#pragma once
#include "Defines.h"
#include <memory>

namespace Prospect
{
   class Scene_impl;
   class Entity;

   class Scene
   {
   public:
      EXPORT_DLL ~Scene();
      Scene();

      EXPORT_DLL Entity& AddEntity();
      EXPORT_DLL Entity& GetEntity(const int index);

      //void CreateCamera(const glm::ivec2& size);
      EXPORT_DLL void CreateTerrain();
      //Camera& GetCamera() const;

      Scene_impl& GetImpl();

   private:
      std::unique_ptr<Scene_impl> m_impl;
   };
}