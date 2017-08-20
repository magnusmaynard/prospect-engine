#pragma once
#include "Defines.h"
#include <memory>

namespace Prospect
{
   class Scene_impl;


   class Scene
   {
   public:
      EXPORT_API ~Scene();
      Scene();
      Scene_impl& GetImpl();
      const Scene_impl& GetImpl() const;

      //void CreateCamera(const glm::ivec2& size);
      EXPORT_API void CreateTerrain();
      //Camera& GetCamera() const;

   private:
      std::unique_ptr<Scene_impl> m_impl;
   };
}