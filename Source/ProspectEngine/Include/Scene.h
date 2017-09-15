#pragma once
#include "Defines.h"
#include <memory>

namespace Prospect
{
   class Scene_impl;

   class Mesh;
   class Material;
   class Entity;
   class Camera;

   class Scene
   {
   public:
      //Public
      EXPORT_DLL ~Scene();

      EXPORT_DLL Entity& CreateEntity(Mesh& mesh, Material& material);
      EXPORT_DLL Entity& GetEntityAtIndex(const int index);

      EXPORT_DLL const Camera& GetCamera() const;
      EXPORT_DLL Camera& GetCamera();

      //Internal
      Scene();

   private:
      std::unique_ptr<Scene_impl> m_impl;

      friend class Engine_impl;
   };
}