#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Renderable.h"

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
      //RenderableMaterial& material = GetRenderable(entity.GetMaterial());
      //if (currentMaterial != material->GetID())
      //{
      //   material.Bind();
      //}

      //RenderableMesh& mesh = GetRenderable(entity.GetMesh());

      //if (currentMesh != currentMesh->GetID())
      //{
      //   mesh.Bind();
      //}

      //BindTransform(entity.GetTransform());

      //Render(scene, mesh);


      Renderable& renderable = GetRenderable(entity.GetImpl());
      renderable.Render(scene);
   }
}

Renderable& Renderer::GetRenderable(Entity_impl& entity)
{
   auto itr = m_renderables.find(entity.GetID());
   if(itr == m_renderables.end())
   {
      return m_renderables.emplace(entity.GetID(), Renderable(entity, GetRenderableMesh(entity.GetMesh()))).first->second;
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

void Renderer::ApplyCommonUniforms(Scene_impl& scene)
{
   const Camera* camera = scene.GetCamera();

   glUniformMatrix4fv(0, 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
}

void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
