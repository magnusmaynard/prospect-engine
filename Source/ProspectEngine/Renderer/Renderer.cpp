#include "Renderer.h"
#include "Scene/Scene_impl.h"
#include "Scene/Terrain.h"

using namespace Prospect;

Renderer::Renderer()
{
}

void Renderer::Render(Scene_impl& scene)
{
   //Iterate through and render scene graph.

   const Camera* camera = scene.GetCamera();
   if (camera != nullptr)
   {
      //Constants.
      glUniformMatrix4fv(0, 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
      glUniformMatrix4fv(1, 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
   }

   Terrain* terrain = scene.GetTerrain();
   if (terrain != nullptr)
   {
      Render(*terrain);
   }
}


void Renderer::Render(Terrain& terrain)
{
   //Render terrain.
   terrain.Draw();
}
