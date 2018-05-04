#include "ProspectEngine_pch.h"

#include "ShadowMaps.h"
#include "Engine/EngineDefines.h"
#include "Scene/Lights/DirectionalLight_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Renderer/Frustum.h"
#include "Renderer/Debugger/Debug.h"

using namespace Prospect;
using namespace glm;

ShadowMaps::ShadowMaps()
{
   glCreateFramebuffers(1, &m_shadowFBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   const int mipmapLevels = 1;
   glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_shadowTextures);
   glTextureStorage3D(m_shadowTextures, mipmapLevels, GL_DEPTH_COMPONENT32F, TEXTURE_SIZE.x, TEXTURE_SIZE.y, Defines::MAX_SHADOW_MAPS);

   //TODO: use mipmaps
   //glTextureParameteri(m_shadowTextures, GL_TEXTURE_BASE_LEVEL, 0);
   //glTextureParameteri(m_shadowTextures, GL_TEXTURE_MAX_LEVEL, mipmapLevels);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

   //GLfloat maxAnistropy;
   //glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnistropy);
   //glTextureParameterf(m_shadowTextures, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnistropy);

   float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   glTextureParameterfv (m_shadowTextures, GL_TEXTURE_BORDER_COLOR, borderColor);

   //Required for shadow sampler.
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

   //Bind temporary texture layer. 
   BindShadowMap(0);

   const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (error != GL_FRAMEBUFFER_COMPLETE)
   {
      std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   }
}

ShadowMaps::~ShadowMaps()
{
   //TODO: delete fbo and textures.
}

void ShadowMaps::Clear()
{
   static GLfloat ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   glClearNamedFramebufferfv(m_shadowFBO, GL_DEPTH, 0, ones);
}

void ShadowMaps::Update(Scene_impl& scene)
{
   for (int i = 0; i < scene.GetLightCount(); i++)
   {
      ILight_impl* light = scene.GetLightImpl(i);

      if (light->GetCastShadows() &&
         light->GetType() == LightType::Directional)
      {
         DirectionalLight_impl& directionalLight = *static_cast<DirectionalLight_impl*>(light);

         //if (directionalLight.GetShadowCascadeCount() > 1)
         //{
            UpdateShadowMapCascades(directionalLight, scene.GetCameraImpl());
         //}
         //else
         //{
         //   UpdateShadowMap(directionalLight);
         //}
      }
      else
      {
         //Do nothing.
      }
   }
}

int ShadowMaps::Count() const
{
   return m_shadowMaps.size();
}

void ShadowMaps::Bind(const int index)
{
   //TODO: Remove/optimize this.
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
   glViewport(0, 0, TEXTURE_SIZE.x, TEXTURE_SIZE.y);

   BindShadowMap(index);
}

mat4 ShadowMaps::GetViewMatrix(const int index) const
{
   return m_shadowMaps[index].GetViewMatrix();
}

mat4 ShadowMaps::GetProjectionMatrix(const int index) const
{
   return m_shadowMaps[index].GetProjectionMatrix();
}

mat4 ShadowMaps::GetShadowMatrix(const int index) const
{
   return m_shadowMaps[index].GetShadowMatrix();
}

float ShadowMaps::GetFarClipDepth(const int index) const
{
   return m_shadowMaps[index].GetFarClipDepth();
}

GLuint ShadowMaps::GetTexture() const
{
   return m_shadowTextures;
}

void ShadowMaps::UpdateShadowMapCascades(DirectionalLight_impl& light, const Camera_impl& camera)
{
   const mat4 cameraInverseView = camera.GetInverseView();
   const mat4 cameraView = camera.GetView();
   const float cameraNear = camera.GetNear();
   const float cameraFar = camera.GetFar();
   const float cameraDistance = cameraFar - cameraNear;

   const auto& cascades = light.GetShadowCascades();
   const int cascadeCount = static_cast<int>(cascades.size());

   float near = cameraNear;

   for (int i = 0; i < cascadeCount; ++i)
   {
      const float cascadeSize = cascades[i] * cameraDistance;
      const float far = near + cascadeSize;

      const Frustum frustum(near, far, camera.GetFov(), camera.GetAspectRatio());

      //Get centre of frustum in world space.
      Bounds worldFrustumBounds;
      for (auto& c : frustum.Corners)
      {
         //Transform to world space.
         const vec3 corner = cameraInverseView * vec4(c, 1);

         //Calculate bounding box.
         worldFrustumBounds.Min = min(worldFrustumBounds.Min, corner);
         worldFrustumBounds.Max = max(worldFrustumBounds.Max, corner);
      }

      const auto cascadeCentre = worldFrustumBounds.GetCentre();

      const mat4 lightView = lookAt(
         cascadeCentre,
         cascadeCentre + light.GetDirection(),
         Defines::POS_Y);

      Bounds lightFrustumBounds;
      for (auto& c : frustum.Corners)
      {
         //Transform from view to world to light space.
         const vec3 corner = lightView * cameraInverseView * vec4(c, 1);

         //Calculate bounding box.
         lightFrustumBounds.Min = min(lightFrustumBounds.Min, corner);
         lightFrustumBounds.Max = max(lightFrustumBounds.Max, corner);
      }

      ShadowMap& shadowMap = GetShadowMap(light, i);

      shadowMap.Update(lightFrustumBounds, cascadeCentre, light.GetDirection(), far);

      //Update near cascade.
      near = far;
   }
}

ShadowMap& ShadowMaps::GetShadowMap(DirectionalLight_impl& light, const int cascadeIndex)
{
   int shadowMapIndex = light.GetShadowMapIndex();

   if (shadowMapIndex == Defines::INVALID_SHADOW_MAP_ID)
   {
      shadowMapIndex = m_shadowMaps.size();

      for (size_t i = 0; i < light.GetShadowCascades().size(); ++i)
      {
         m_shadowMaps.push_back(ShadowMap());
      }

      light.SetShadowMapIndex(shadowMapIndex);
   }
   else
   {
      //Return existing shadow map.
      shadowMapIndex = light.GetShadowMapIndex();
   }

   return m_shadowMaps[shadowMapIndex + cascadeIndex];
}

void ShadowMaps::UpdateShadowMap(DirectionalLight_impl& light)
{
   //ShadowMap* shadowMap = nullptr;

   //if (light.GetShadowMapIndex() == INVALID_SHADOW_MAP_ID)
   //{
   //   const int newIndex = m_shadowMaps.size();
   //   light.SetShadowMapIndex(newIndex);

   //   m_shadowMaps.push_back(ShadowMap());

   //   shadowMap = &m_shadowMaps[newIndex];

   //}
   //else
   //{
   //   shadowMap = &m_shadowMaps[light.GetShadowMapIndex()];
   //}

   //shadowMap->Update(light);
}

void ShadowMaps::BindShadowMap(const int index) const
{
   glNamedFramebufferTextureLayer(m_shadowFBO, GL_DEPTH_ATTACHMENT, m_shadowTextures, 0, index);
}


