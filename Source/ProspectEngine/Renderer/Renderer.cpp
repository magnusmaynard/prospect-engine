#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/ILight_impl.h"
#include "Renderer/Debugger/Debug.h"
#include "Libraries/MaterialLibrary_impl.h"
#include "Renderer/ShadowMap.h"

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
   m_lightingPass(m_shaderLibrary, m_gBuffer, m_shadowMaps),
   m_entityRenderer(m_shaderLibrary),
   m_terrainRenderer(m_shaderLibrary),
   m_atmosphereRenderer(m_shaderLibrary),
   m_sunRenderer(m_shaderLibrary),
   m_textRenderer(m_shaderLibrary),
   m_fpsText("", ivec2(4, 0), 12)
{
   Initialise();
}

void Renderer::Initialise()
{
#ifdef _DEBUG
   glEnable(GL_DEBUG_OUTPUT);
#endif

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   glEnable(GL_BLEND);

   glEnable(GL_CULL_FACE);
   glFrontFace(GL_CCW);

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
   UpdateFPS(time);

   Clear();
   m_gBuffer.Clear();

   ShadowPass(scene);
   GeometryPass(scene);
   LightingPass2();
   EffectsPass(scene);

   Debug::CheckErrors();
}

void Renderer::ShadowPass(Scene_impl& scene)
{
   m_shadowMaps.Update(scene);

   for (int i = 0; i < m_shadowMaps.Count(); i++)
   {
      m_shadowMaps.Bind(i);
      m_shadowMaps.Clear();

      //Update camera to lights perspective.
      CameraUniforms camera;
      camera.PerspectiveProjection = m_shadowMaps.GetProjectionMatrix(i);
      camera.View = m_shadowMaps.GetViewMatrix(i);
      m_globalUniformBuffers.Camera.Update(camera);

      //Render scene.
      RenderEntities(scene.GetRootEntityImpl());
   }

   //Reset camera back to normal.
   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));
}

void Renderer::GeometryPass(Scene_impl& scene)
{
   m_gBuffer.Bind();

   RenderEntities(scene.GetRootEntityImpl());

   if(auto* terrain = scene.GetTerrainImpl())
   {
      m_terrainRenderer.Render(*terrain);
   }

   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      m_sunRenderer.Render(*atmosphere);
   }
}

void Renderer::RenderEntities(Entity_impl& entity)
{
   m_entityRenderer.Render(entity);

   auto& children = entity.GetChildren();
   for (auto& child : children)
   {
      //TODO: make non-recursive, don't store entities in a graph.
      RenderEntities(*child.get());
   }
}

void Renderer::LightingPass2()
{
   BindDefaultFramebuffer();

   m_lightingPass.Render();
}

void Renderer::EffectsPass(Scene_impl& scene)
{
   BindDefaultFramebuffer();

   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      m_atmosphereRenderer.Render(*atmosphere, m_gBuffer);
   }

   if (m_showFPS)
   {
      m_textRenderer.Render(m_fpsText);
   }
}

void Renderer::UpdateGlobalUniformBuffers(const Scene_impl& scene)
{
   const Camera_impl& camera = scene.GetCameraImpl();

   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));

   m_globalUniformBuffers.MaterialLibrary.Update(MaterialLibraryUniforms(m_materialLibrary));

   std::vector<const DirectionalLight_impl*> directionalLights;

   for(int i = 0; i < scene.GetLightCount(); i++)
   {
      const ILight_impl* light = scene.GetLightImpl(i);

      switch (light->GetType())
      {
      case LightType::Directional:
         directionalLights.push_back(static_cast<const DirectionalLight_impl*>(light));
         break;
      case LightType::Spot:
      case LightType::Point:
      default:
         //Do nothing.
         break;
      }
   }

   m_globalUniformBuffers.DirectionalLights.Update(DirectionalLightListUniforms(directionalLights));
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
   glViewport(0, 0, m_size.x, m_size.y);
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
   m_size = size;
   m_gBuffer.Resize(size);
}

void Renderer::UpdateFPS(const double time)
{
   static const double FPS_INTERVAL = 1000.0;

   m_frameCount++;

   if (time - m_previousTime >= FPS_INTERVAL)
   {
      const std::string text = std::to_string(m_frameCount);

      m_fpsText.SetText(text);

      m_frameCount = 0;
      m_previousTime = time;
   }
}

