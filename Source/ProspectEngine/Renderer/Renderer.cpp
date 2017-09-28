#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Scene/Camera_impl.h"
#include "Renderables/RenderableEntity.h"
#include "Libraries/EntityLibrary.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer()
{
}

void Renderer::Setup()
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::Render(Scene_impl& scene)
{
   Clear();

   scene.UpdateTransforms();

   UpdateUniformBuffer(scene);

   UpdateEntityRenderables(scene.GetEntityLib());

   //Render all renderables.
   for (auto& renderable : m_renderables)
   {
      renderable->Render(m_uniformBuffer);
   }
}

void Renderer::UpdateEntityRenderables(EntityLibrary& entityLib)
{
   for (int i = 0; i < entityLib.Count(); ++i)
   {
      Entity_impl& entity = *entityLib[i].m_impl;

      if (entity.GetMesh() != nullptr && entity.GetMaterial() != nullptr)
      {
         if(entity.GetRenderable() == nullptr)
         {
            m_renderables.push_back(std::make_unique<RenderableEntity>(
               entity, GetRenderableMesh(*entity.GetMeshImpl())));

            entity.SetRenderable(m_renderables.back().get());
         }
      }
   }
}

RenderableMesh& Renderer::GetRenderableMesh(Mesh_impl& mesh)
{
   auto itr = m_renderableMeshes.find(mesh.GetID());
   if (itr == m_renderableMeshes.end())
   {
      return m_renderableMeshes.emplace(mesh.GetID(), RenderableMesh(mesh)).first->second;
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
