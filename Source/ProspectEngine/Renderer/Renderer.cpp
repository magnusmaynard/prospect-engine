#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/Light_impl.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Renderer/Debugger/Debug.h"
#include "Libraries/MaterialLibrary_impl.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer(const MaterialLibrary_impl& materialLibrary, const ivec2& size)
   :
   m_showFPS(false),
   m_showWireframe(false),
   m_frameCount(0),
   m_previousTime(0),
   m_shaderLibrary(m_globalUniformBuffers),
   m_materialLibrary(materialLibrary),
   m_gBuffer(size),
   m_lightingPass(m_shaderLibrary, m_gBuffer)
{
   Initialize();
}

void Renderer::Initialize()
{
#ifdef _DEBUG
   glEnable(GL_DEBUG_OUTPUT);
#endif

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   glEnable(GL_BLEND);

   glEnable(GL_CULL_FACE);
   glFrontFace(GL_CCW);

   m_fpsText = std::make_unique<RenderableText>(m_shaderLibrary, "", ivec2(4, 0), 12);

   CreateShadowMap();//TEMP
}

void Renderer::UpdateState()
{
   if (m_showWireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }
   else
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }

   glEnable(GL_DEPTH_TEST);
}

void Renderer::Render(const double time, Scene_impl& scene)
{
   UpdateState();
   UpdateGlobalUniformBuffers(scene);
   UpdateRenderableEntity(scene.GetRootEntityImpl());
   UpdateRenderableTerrain(scene);
   UpdateRenderableAtmosphere(scene);
   UpdateRenderableSun(scene);
   UpdateFPS(time);

   Clear();
   m_gBuffer.Clear();

   //TEMP
   static GLfloat ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   glClearNamedFramebufferfv(m_shadowFBO, GL_DEPTH, 0, ones);


   //Shadow maps.
   ShadowPasses(scene);

   //Geometry pass.
   m_gBuffer.Bind();
   GeometryPass();

   //Lighting pass.
   BindDefaultFramebuffer();

   //TEMP
   m_lightingPass.Render(m_shadowTexture, GetShadowMatrix(scene.GetAtmosphereImpl()->GetLightImpl()));

   //Effects pass.
   EffectsPass();

   Debug::CheckErrors();
}


void Renderer::GeometryPass()
{
   for (auto& renderable : m_renderables)
   {
      renderable->Render();
   }

   if (m_terrain)
   {
      m_terrain->Render();
   }

   if (m_sun)
   {
      m_sun->Render();
   }

   if (m_showFPS)
   {
      m_fpsText->Render();
   }
}

mat4 Renderer::GetShadowMatrix(const Light_impl& light) const
{
   const mat4 lightProjection = ortho(-100.f, 100.f, -100.f, 100.f, -1000.f, 1000.f);
   const mat4 lightView = lookAt(light.GetPosition() - light.GetDirection(), light.GetPosition(), POS_Y);
   const mat4 lightModel = mat4(1.0);

   //Move [-1, 1] space to [0, 1] required for sampling textures.
   const mat4 biasMatrix(
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0
   );

   return biasMatrix * lightProjection * lightView * lightModel;
}

void Renderer::ShadowPasses(Scene_impl& scene)
{
   //Update to light perspective.
   
   //TODO: for each light.

   const Light_impl& light = scene.GetAtmosphereImpl()->GetLightImpl();

   const mat4 lightProjection = ortho(-100.f, 100.f, -100.f, 100.f, -1000.f, 1000.f);
   const mat4 lightView = lookAt(light.GetPosition() - light.GetDirection(), light.GetPosition(), POS_Y);

   CameraUniforms camera(scene.GetCameraImpl());
   camera.PerspectiveProjection = lightProjection;
   camera.View = lightView;

   //Update camera to lights perspective.
   m_globalUniformBuffers.Camera.Update(camera);

   //Bind Shadow Framebuffer
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   //Render scene.
   for (auto& renderable : m_renderables)
   {
      renderable->Render();
   }

   //Reset camera back to normal.
   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));
}

void Renderer::EffectsPass()
{
   BindDefaultFramebuffer();

   if (m_atmosphere)
   {
      m_atmosphere->Render();
   }
}

void Renderer::UpdateRenderableEntity(Entity_impl& entity)
{
   if (entity.ChildEntityAdded())
   {
      if (entity.GetRenderable() == nullptr &&
         entity.GetMeshImpl() != nullptr &&
         entity.GetMaterialImpl() != nullptr)
      {
         VertexData& vertexData = GetVertexData(*entity.GetMeshImpl());

         m_renderables.push_back(std::make_unique<RenderableEntity>(m_shaderLibrary, entity, vertexData));

         entity.SetRenderable(m_renderables.back().get());
      }

      auto& children = entity.GetChildren();
      for (auto& child : children)
      {
         UpdateRenderableEntity(*child.get());
      }

      entity.ResetChildEntityAdded();
   }
}

VertexData& Renderer::GetVertexData(Mesh_impl& mesh)
{
   auto itr = m_vertexDataMap.find(mesh.GetID());
   if (itr == m_vertexDataMap.end())
   {
      return m_vertexDataMap.emplace(mesh.GetID(), VertexData(mesh)).first->second;
   }
   
   return itr->second;
}

void Renderer::UpdateGlobalUniformBuffers(const Scene_impl& scene)
{
   const Camera_impl& camera = scene.GetCameraImpl();

   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));

   m_globalUniformBuffers.MaterialLibrary.Update(MaterialLibraryUniforms(m_materialLibrary));

   std::vector<const Light_impl*> lights;

   //Atmosphere lights.
   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      lights.push_back(&atmosphere->GetLightImpl());
   }

   //Scene lights.
   for(int i = 0; i < scene.GetLightCount(); i++)
   {
      lights.push_back(scene.GetLightImpl(i));
   }

   m_globalUniformBuffers.Lights.Update(LightsUniforms(lights));
}

void Renderer::UpdateRenderableTerrain(const Scene_impl& scene)
{
   if(m_terrain == nullptr)
   {
      const Terrain_impl* terrain = scene.GetTerrainImpl();
      if (terrain)
      {
         m_terrain = std::make_unique<RenderableTerrain>(m_shaderLibrary, *terrain);
      }
   }
}

void Renderer::UpdateRenderableAtmosphere(const Scene_impl& scene)
{
   if (m_atmosphere == nullptr)
   {
      if (const auto atmosphere = scene.GetAtmosphereImpl())
      {
         m_atmosphere = std::make_unique<RenderableAtmosphere>(m_shaderLibrary, m_gBuffer, *atmosphere);

         atmosphere->SetRenderable(m_atmosphere.get());
      }
   }
}

void Renderer::UpdateRenderableSun(const Scene_impl& scene)
{
   if (const auto atmosphere = scene.GetAtmosphereImpl())
   {
      if (m_sun == nullptr)
      {
         m_sun = std::make_unique<RenderableSun>(m_shaderLibrary);
      }

      m_sun->UpdateUniforms(*atmosphere);
   }
}

void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   ClearDepthBuffer();
}

void Renderer::ClearDepthBuffer()
{
   glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::BindDefaultFramebuffer()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::CreateShadowMap()
{
   glCreateFramebuffers(1, &m_shadowFBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   glCreateTextures(GL_TEXTURE_2D, 1, &m_shadowTexture);
   glTextureStorage2D(m_shadowTexture, 1, GL_DEPTH_COMPONENT32F, 1280, 720);

   glTextureParameteri(m_shadowTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   //Require for shadow sampler.
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

   glNamedFramebufferTexture(m_shadowFBO, GL_DEPTH_ATTACHMENT, m_shadowTexture, 0);

   const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (error != GL_FRAMEBUFFER_COMPLETE)
   {
      std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   }

   BindDefaultFramebuffer();
}

void Renderer::ShowFPS(const bool showFPS)
{
   m_showFPS = showFPS;
}

void Renderer::ShowWireframe(const bool showWireframe)
{
   m_showWireframe = showWireframe;
}

void Renderer::Resize(const ivec2& size)
{
   m_gBuffer.Resize(size);
}

void Renderer::UpdateFPS(const double time)
{
   static const double FPS_INTERVAL = 1000.0;

   m_frameCount++;

   if (time - m_previousTime >= FPS_INTERVAL)
   {
      const std::string text = std::to_string(m_frameCount);

      m_fpsText->SetText(text);

      m_frameCount = 0;
      m_previousTime = time;
   }
}

