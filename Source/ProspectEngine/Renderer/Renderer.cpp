#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/ILight_impl.h"
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

   ShadowPass(scene);
   GeometryPass();
   LightingPass2();
   EffectsPass();

   Debug::CheckErrors();
}

void Renderer::GeometryPass()
{
   m_gBuffer.Bind();

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

void Renderer::LightingPass2()
{
   BindDefaultFramebuffer();

   //TEMP
   m_lightingPass.Render(m_shadowMaps[0]);
}

void Renderer::UpdateShadowMap(DirectionalLight_impl& light)
{
   ShadowMap* shadowMap = nullptr;
   if(light.GetShadowMapIndex() == INVALID_SHADOW_MAP_ID)
   {
      const int newIndex = m_shadowMaps.size();
      m_shadowMaps.push_back(ShadowMap(light));
      light.SetShadowMapIndex(newIndex);

      shadowMap = &m_shadowMaps[newIndex];
      shadowMap->Initialise();
   }
   else
   {
      shadowMap = &m_shadowMaps[light.GetShadowMapIndex()];
   }

   shadowMap->Clear();
   shadowMap->Bind();

   //TODO: This sucks, the light should not be responsible for the shadow map caching.
   if(light.GetIsDirty())
   {
      light.SetIsDirty(false);
      shadowMap->MakeDirty();
   }

   //Update camera to lights perspective.
   CameraUniforms camera;
   camera.PerspectiveProjection = shadowMap->GetProjection();
   camera.View = shadowMap->GetView();
   m_globalUniformBuffers.Camera.Update(camera);

   //Render scene.
   for (auto& renderable : m_renderables)
   {
      //if(renderable->GetCastShadow())
      renderable->Render();
   }
}

void Renderer::ShadowPass(Scene_impl& scene)
{
   for (int i = 0; i < scene.GetLightCount(); i++)
   {
      ILight_impl* light = scene.GetLightImpl(i);

      if(light->GetCastShadows() &&
         light->GetType() == LightType::Directional)
      {
         UpdateShadowMap(*static_cast<DirectionalLight_impl*>(light));
      }
      else
      {
         //Do nothing.
      }
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

      m_fpsText->SetText(text);

      m_frameCount = 0;
      m_previousTime = time;
   }
}

