#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Libraries/EntityLibrary.h"

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
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   m_fpsText = std::make_unique<RenderableText>(
      m_globalUniformBuffers, "", ivec2(2, 2), 18);
}

void Renderer::Render(double time, Scene_impl& scene)
{
   if(m_showWireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }
   else
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }

   Clear();

   UpdateUniformBuffer(scene);
   UpdateRenderableEntities(scene.GetEntityLib());
   UpdateRenderableTerrain(scene);

   //Render all renderables.
   for (auto& renderable : m_renderableEntities)
   {
      renderable->Render();
   }

   if (m_renderableTerrain)
   {
      m_renderableTerrain->Render();
   }

   if (m_showFPS)
   {
      m_fpsText->SetScreenSize(scene.GetCamera().GetSize()); //TODO: Pass ortho projection via UniformBuffer

      UpdateFPS(time);
      m_fpsText->Render();
   }
}

void Renderer::UpdateRenderableEntities(EntityLibrary& entityLib)
{
   for (int i = 0; i < entityLib.Count(); ++i)
   {
      Entity_impl& entity = *entityLib[i].m_impl;

      if (entity.GetMesh() != nullptr && entity.GetMaterial() != nullptr)
      {
         if(entity.GetRenderable() == nullptr)
         {
            VertexData& vertexData = GetVertexData(*entity.GetMeshImpl());

            m_renderableEntities.push_back(std::make_unique<RenderableEntity>(entity, vertexData, m_globalUniformBuffers));

            entity.SetRenderable(m_renderableEntities.back().get());
         }
      }
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

void Renderer::UpdateUniformBuffer(const Scene_impl& scene)
{
   const Camera_impl& camera = scene.GetCameraImpl();

   m_globalUniformBuffers.Camera.Update(
   {
      camera.GetProjectionMatrix(),
      camera.GetViewMatrix()
   });
}

void Renderer::UpdateRenderableTerrain(const Scene_impl& scene)
{
   if(m_renderableTerrain == nullptr)
   {
      const Terrain* terrain = scene.GetTerrain();
      if (terrain)
      {
         m_renderableTerrain = std::make_unique<RenderableTerrain>(*terrain, m_globalUniformBuffers);
      }
   }
}


void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
