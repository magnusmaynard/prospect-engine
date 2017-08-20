#pragma once
#include <memory>
#include "Terrain.h"
#include "Camera.h"
#include "Include/Scene.h"

namespace Prospect
{
   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      void CreateCamera(const glm::ivec2& size);
      void CreateTerrain();

      Camera* GetCamera();
      const Camera* GetCamera() const;

      Terrain* Scene_impl::GetTerrain();
      const Terrain* Scene_impl::GetTerrain() const;

   private:
      Scene& m_parent;
      std::unique_ptr<Camera> m_camera;
      std::unique_ptr<Terrain> m_terrain;
   };
}
