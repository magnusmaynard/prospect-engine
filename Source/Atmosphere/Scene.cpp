#include "Scene.h"

using namespace Prospect;

Scene::Scene()
{
}

void Scene::CreateCamera(const glm::ivec2& size)
{
   m_camera = std::make_unique<Camera>(size);
}

void Scene::CreateTerrain()
{
   m_terrain = std::make_unique<Terrain>();
}

Camera& Scene::GetCamera() const
{
   return *m_camera;
}

void Scene::Render()
{
   if (m_camera == nullptr)
   {
      throw std::exception("The must contain a camera to render the scene.");
   }

   //Constants.
   glUniformMatrix4fv(0, 1, GL_FALSE, &m_camera->GetViewMatrix()[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &m_camera->GetProjectionMatrix()[0][0]);

   //Update.
   //m_terrain->Update();
   m_terrain->Draw();
}
