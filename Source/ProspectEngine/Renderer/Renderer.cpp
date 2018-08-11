#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/ILight_impl.h"
#include "Renderer/Debugger/Debug.h"
#include "Libraries/MaterialLibrary_impl.h"
#include "Renderer/Shadows/ShadowMap.h"
#include "Scene2D/Scene2D_impl.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer(MaterialLibrary_impl& materialLibrary, const ivec2& size)
   :
   m_showWireframe(false),
   m_shaderLibrary(m_globalUniformBuffers),
   m_materialLibrary(materialLibrary),
   m_gBuffer(size),
   m_displayBuffer(size),
   m_effectsBuffer(size),
   m_entityRenderer(m_shaderLibrary),
   m_terrainRenderer(m_shaderLibrary, materialLibrary),
   m_sunRenderer(m_shaderLibrary, materialLibrary),
   m_textRenderer(m_shaderLibrary),
   m_lightingRenderer(m_shaderLibrary),
   m_atmosphereRenderer(m_shaderLibrary),
   m_godRaysRenderer(m_shaderLibrary)
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

   Debug::Points::Initialise(m_shaderLibrary);
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

void Renderer::Render(const double time, Scene_impl& scene, Scene2D_impl& scene2D)
{
   UpdateState();
   UpdateGlobalUniformBuffers(scene);

   Clear();
   m_gBuffer.Clear();
   m_displayBuffer.Clear();
   m_effectsBuffer.Clear();

   ShadowPass(scene);
   GeometryPass(scene);
   LightingPass(scene);
   EffectsPass(scene, scene2D);

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

      if (auto* terrain = scene.GetTerrainImpl())
      {
         m_terrainRenderer.Render(*terrain);
      }
   }

   //Reset camera back to normal.
   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));
}

void Renderer::GeometryPass(Scene_impl& scene)
{
   m_gBuffer.Bind();

   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      m_sunRenderer.Render(*atmosphere);
   }

   RenderEntities(scene.GetRootEntityImpl());

   if (auto* terrain = scene.GetTerrainImpl())
   {
      m_terrainRenderer.Render(*terrain);
   }
}

void Renderer::LightingPass(Scene_impl& scene)
{
   m_displayBuffer.Bind();

   m_lightingRenderer.Render(m_gBuffer, m_shadowMaps);

   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      m_atmosphereRenderer.Render(*atmosphere, m_gBuffer);
   }
}

void Renderer::EffectsPass(Scene_impl& scene, Scene2D_impl& scene2D)
{
   m_displayBuffer.CopyTo(m_effectsBuffer.GetFramebufferName());

   m_effectsBuffer.Bind();

   if (scene.GetAtmosphereImpl() != nullptr)
   {
      const vec3 sunPosition = scene.GetAtmosphereImpl()->GetSunDirection() * -1000.f;

      m_godRaysRenderer.Render(m_gBuffer, m_displayBuffer, sunPosition);
   }

   //TODO: Improve 2d scene rendering, make more generic.
   for (int i = 0; i < scene2D.GetTextCount(); i++)
   {
      m_textRenderer.Render(scene2D.GetTextByIndex(i));
   }

   m_effectsBuffer.CopyTo(DEFAULT_FRAMEBUFFER);
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
   glBindFramebuffer(GL_FRAMEBUFFER, DEFAULT_FRAMEBUFFER);
   glViewport(0, 0, m_size.x, m_size.y);
}

void Renderer::ShowWireframe(const bool showWireframe)
{
   m_showWireframe = showWireframe;
}

void Renderer::Resize(const ivec2& size)
{
   m_size = size;
   m_gBuffer.Resize(size);
   m_displayBuffer.Resize(size);
   m_effectsBuffer.Resize(size);
}

