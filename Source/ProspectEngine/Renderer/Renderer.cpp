#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/Light_impl.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer()
   :
   m_frameCount(0),
   m_previousTime(0),
   m_showFPS(false),
   m_showWireframe(false)
{
   Initialize();
}

void Renderer::Initialize()
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   glEnable(GL_BLEND);

   //glEnable(GL_CULL_FACE);
   //glFrontFace(GL_CCW);

   m_fpsText = std::make_unique<RenderableText>(
      m_globalUniformBuffers, "", ivec2(4, 0), 12);
}

void Renderer::Render(double time, Scene_impl& scene)
{
   //Pre Render
   if(m_showWireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }
   else
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }

   Clear();

   //Update
   UpdateGlobalUniformBuffers(scene);
   UpdateRenderableEntity(scene.GetRootEntityImpl());
   UpdateRenderableTerrain(scene);
   UpdateRenderableAtmosphere(scene);

   //Background
   if (m_atmosphere)
   {
      m_atmosphere->Render();
   }

   ClearDepthBuffer();

   //Foreground
   for (auto& renderable : m_renderables)
   {
      renderable->Render();
   }

   if (m_terrain)
   {
      m_terrain->Render();
   }

   //HUD
   if (m_showFPS)
   {
      UpdateFPS(time);
      m_fpsText->Render();
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

         m_renderables.push_back(std::make_unique<RenderableEntity>(m_globalUniformBuffers, entity, vertexData));

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

   //TODO: Get all lights
   //m_globalUniformBuffers.DirectionalLight.Update(DirectionalLightUniforms(*scene.GetLightImpl(0)));
}

void Renderer::UpdateRenderableTerrain(const Scene_impl& scene)
{
   if(m_terrain == nullptr)
   {
      const Terrain_impl* terrain = scene.GetTerrainImpl();
      if (terrain)
      {
         m_terrain = std::make_unique<RenderableTerrain>(m_globalUniformBuffers, *terrain);
      }
   }
}

void Renderer::UpdateRenderableAtmosphere(const Scene_impl& scene)
{
   if (m_atmosphere == nullptr)
   {
      if (const auto atmosphere = scene.GetAtmosphereImpl())
      {
         m_atmosphere = std::make_unique<RenderableAtmosphere>(m_globalUniformBuffers, *atmosphere);

         atmosphere->SetRenderable(m_atmosphere.get());
      }
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

void Renderer::ShowFPS(bool showFPS)
{
   m_showFPS = showFPS;
}

void Renderer::ShowWireframe(bool showWireframe)
{
   m_showWireframe = showWireframe;
}

void Renderer::UpdateFPS(double time)
{
   static const double FPS_INTERVAL = 1000.0;

   m_frameCount++;

   if (time - m_previousTime >= FPS_INTERVAL)
   {
      std::string text = std::to_string(m_frameCount);

      m_fpsText->SetText(text);

      m_frameCount = 0;
      m_previousTime = time;
   }
}
