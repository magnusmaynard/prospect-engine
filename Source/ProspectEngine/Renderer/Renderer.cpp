#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "RenderableEntity.h"
#include <iostream>

using namespace Prospect;

Renderer::Renderer()
{
}

void Renderer::Render(Scene_impl& scene)
{
   for(auto& entity : scene.GetEntities()) //TODO: is this optimized out?
   {
      RenderableEntity& renderable = GetRenderable(entity.GetImpl());

      Render(renderable);
   }

   //const Camera* camera = scene.GetCamera();
   //if (camera != nullptr)
   //{
   //   //Constants.
   //   glUniformMatrix4fv(0, 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
   //   glUniformMatrix4fv(1, 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
   //}

   //Terrain* terrain = scene.GetTerrain();
   //if (terrain != nullptr)
   //{
   //   //Render terrain.
   //}
}

RenderableEntity& Renderer::GetRenderable(Entity_impl& entity)
{
   //Returns the found or emplaced value.
   return m_renderables.emplace(
      entity.GetID(), RenderableEntity(entity)).first->second;
}

void Renderer::Render(RenderableEntity& renderable)
{
   //Apply program

   //Apply common uniforms

   //Applt transform

   //Apply Material

   //Apply Mesh

   //Render
   std::cout << renderable.m_entity.GetID() << std::endl;
}