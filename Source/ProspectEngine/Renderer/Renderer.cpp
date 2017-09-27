#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Scene/Camera_impl.h"
#include "Renderables/Renderable.h"
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

   UpdateRenderables(scene.GetEntityLib());

   //Render all renderables.
   for (auto& renderable : m_renderables)
   {
      renderable.second.Render(scene);
   }
}

void Renderer::UpdateRenderables(EntityLibrary& entityLib)
{
   for (int i = 0; i < entityLib.Count(); ++i)
   {
      Entity_impl& entity = *entityLib[i].m_impl;

      if (entity.GetMesh() != nullptr && entity.GetMaterial() != nullptr)
      {
         auto itr = m_renderables.find(entity.GetID());
         if (itr == m_renderables.end())
         {
            m_renderables.emplace(
               entity.GetID(),
               Renderable(
                  entity,
                  GetRenderableMesh(*entity.GetMeshImpl()),
                  GetRenderableMaterial(*entity.GetMaterial())));
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

RenderableMaterial& Renderer::GetRenderableMaterial(Material& material)
{
   auto itr = m_renderableMaterials.find(material.GetID());
   if (itr == m_renderableMaterials.end())
   {
      return m_renderableMaterials.emplace(material.GetID(), RenderableMaterial(material)).first->second;
   }

   return itr->second;
}

void Renderer::ApplyCommonUniforms(Scene_impl& scene)
{
   Camera_impl& camera = scene.GetCameraImpl();

   glUniformMatrix4fv(0, 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
}

void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
