#include "ProspectEngine_pch.h"

#include "ShadowMaps.h"
#include "Engine/EngineDefines.h"
#include "Scene/Lights/DirectionalLight_impl.h"
#include "Scene/Scene_impl.h"

using namespace Prospect;
using namespace glm;

ShadowMaps::ShadowMaps()
{
   glCreateFramebuffers(1, &m_shadowFBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_shadowTextures);
   glTextureStorage3D(m_shadowTextures, 1, GL_DEPTH_COMPONENT32F, TEXTURE_SIZE.x, TEXTURE_SIZE.y, MAX_SHADOW_MAPS);

   glTextureParameteri(m_shadowTextures, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_shadowTextures, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
         UpdateShadowMap(*static_cast<DirectionalLight_impl*>(light));
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

GLuint ShadowMaps::GetTexture() const
{
   return m_shadowTextures;
}

void ShadowMaps::UpdateShadowMap(DirectionalLight_impl& light)
{
   ShadowMap* shadowMap = nullptr;
   if (light.GetShadowMapIndex() == INVALID_SHADOW_MAP_ID)
   {
      const int newIndex = m_shadowMaps.size();
      light.SetShadowMapIndex(newIndex);

      m_shadowMaps.push_back(ShadowMap());

      shadowMap = &m_shadowMaps[newIndex];

   }
   else
   {
      shadowMap = &m_shadowMaps[light.GetShadowMapIndex()];
   }

   shadowMap->Update(light);
}

void ShadowMaps::BindShadowMap(const int index) const
{
   glNamedFramebufferTextureLayer(m_shadowFBO, GL_DEPTH_ATTACHMENT, m_shadowTextures, 0, index);
}
