#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Scene/Camera_impl.h"
#include "Renderables/RenderableEntity.h"
#include "Libraries/EntityLibrary.h"
#include "Scene/Mesh_impl.h"
#include <iostream>
#include "Text/Text.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer()
   :
   m_frameCount(0),
   m_previousTime(0),
   m_showFPS(false)
{
}

void Renderer::Setup()
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


   Text fpsText("Test");
}

void Renderer::Render(double time, Scene_impl& scene)
{
   Clear();

   scene.UpdateTransforms();

   UpdateUniformBuffer(scene);

   UpdateRenderableEntities(scene.GetEntityLib());

   //UpdateRenderableTerrain(scene.GetTerrain());

   //Render all renderables.
   for (auto& renderable : m_renderables)
   {
      renderable->Render(m_uniformBuffer);
   }

   DisplayFPS(time);
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

            m_renderables.push_back(std::make_unique<RenderableEntity>(entity, vertexData, m_shaderFactory));

            entity.SetRenderable(m_renderables.back().get());
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

void Renderer::UpdateUniformBuffer(Scene_impl& scene)
{
   Camera_impl& camera = scene.GetCameraImpl();

   m_uniformBuffer.SetProjectionTransform(camera.GetProjectionMatrix());
   m_uniformBuffer.SetViewTransform(camera.GetViewMatrix());
}

void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::ShowFPS(bool showFPS)
{
   m_showFPS = showFPS;
}

void Renderer::DisplayFPS(double time)
{
   static const double FPS_INTERVAL = 1000.0;

   if (m_showFPS)
   {
      m_frameCount++;

      if(time - m_previousTime >= FPS_INTERVAL)
      {
         std::cout << m_frameCount << std::endl;

         m_frameCount = 0;
         m_previousTime = time;
      }
   }
}