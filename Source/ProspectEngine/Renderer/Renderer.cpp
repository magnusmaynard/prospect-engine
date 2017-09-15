#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Scene/Camera_impl.h"
#include "Renderables/Renderable.h"

using namespace Prospect;

Renderer::Renderer()
{
   //TODO: This currently only supports one shader.
   //Compile program.

   //Use program.

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//TODO: temp
   glEnable(GL_BLEND);
}

void Renderer::Render(Scene_impl& scene)
{
   Clear();

   //BindCamera(scene.GetCamera());

   for(auto& entity : scene.GetEntities()) //TODO: is this optimized out?
   {
      Renderable& renderable = GetRenderable(*entity.m_impl);
      renderable.Render(scene);
   }
}

Renderable& Renderer::GetRenderable(Entity_impl& entity)
{
   auto itr = m_renderables.find(entity.GetID());
   if(itr == m_renderables.end())
   {
      return m_renderables.emplace(
         entity.GetID(),
         Renderable(
            entity,
            GetRenderableMesh(entity.GetMesh()),
            GetRenderableMaterial(entity.GetMaterial()))).first->second;
   }
   else
   {
      return itr->second;
   }
}

RenderableMesh& Renderer::GetRenderableMesh(Mesh& mesh)
{
   auto itr = m_renderableMeshes.find(mesh.GetID());
   if (itr == m_renderableMeshes.end())
   {
      return m_renderableMeshes.emplace(mesh.GetID(), RenderableMesh(mesh)).first->second;
   }
   else
   {
      return itr->second;
   }
}

RenderableMaterial& Renderer::GetRenderableMaterial(Material& material)
{
   auto itr = m_renderableMaterials.find(material.GetID());
   if (itr == m_renderableMaterials.end())
   {
      return m_renderableMaterials.emplace(material.GetID(), RenderableMaterial(material)).first->second;
   }
   else
   {
      return itr->second;
   }
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
