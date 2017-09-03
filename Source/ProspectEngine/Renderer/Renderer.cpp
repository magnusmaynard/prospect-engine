#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"
#include "Renderable.h"

using namespace Prospect;

Renderer::Renderer()
{
}

void Renderer::Render(Scene_impl& scene)
{
   ApplyCommonUniforms(scene);

   for(auto& entity : scene.GetEntities()) //TODO: is this optimized out?
   {
      Renderable& renderable = GetRenderable(entity.GetImpl());

      renderable.Render(scene);
   }

   //Terrain* terrain = scene.GetTerrain();
   //if (terrain != nullptr)
   //{
   //   //Render terrain.
   //}
}

Renderable& Renderer::GetRenderable(Entity_impl& entity)
{
   auto itr = m_renderables.find(entity.GetID());
   if(itr == m_renderables.end())
   {
      return m_renderables.emplace(entity.GetID(), Renderable(entity)).first->second;
   }
   else
   {
      return itr->second;
   }
}

void Renderer::ApplyCommonUniforms(Scene_impl& scene)
{
   const Camera* camera = scene.GetCamera();

   glUniformMatrix4fv(1, 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
   glUniformMatrix4fv(2, 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
}
