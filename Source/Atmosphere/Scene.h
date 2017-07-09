#pragma once
#include "Object.h"
#include <memory>
#include "Terrain.h"
#include "Camera.h"

class Scene
{
public:
   Scene()
   {
   }

   void CreateCamera(const glm::ivec2& size)
   {
      m_camera = std::make_unique<Camera>(size);
   }

   void CreateTerrain()
   {
      m_terrain = std::make_unique<Terrain>();
   }

   Camera& GetCamera() const
   {
      return *m_camera;
   }

   void Render()
   {
      if(m_camera == nullptr)
      {
         throw std::exception("The must contain a camera to render the scene.");
      }

      //Constants.
      glUniformMatrix4fv(0, 1, GL_FALSE, &m_camera->GetViewMatrix()[0][0]);
      glUniformMatrix4fv(1, 1, GL_FALSE, &m_camera->GetProjectionMatrix()[0][0]);

      //Render.
      //m_terrain->Update();
      m_terrain->Draw();
   }

private:
   std::unique_ptr<Camera> m_camera;
   std::unique_ptr<Terrain> m_terrain;
};
