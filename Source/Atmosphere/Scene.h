#pragma once
#include "Object.h"
#include <memory>
#include "Terrain.h"
#include "Camera.h"

namespace Prospect
{
   class Scene
   {
   public:
      Scene();
      void CreateCamera(const glm::ivec2& size);
      void CreateTerrain();
      Camera& GetCamera() const;
      void Render();

   private:
      std::unique_ptr<Camera> m_camera;
      std::unique_ptr<Terrain> m_terrain;
   };
}
