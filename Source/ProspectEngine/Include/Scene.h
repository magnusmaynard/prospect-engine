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
      EXPORT_DLL ~Scene();
      Scene();

      EXPORT_DLL Entity& CreateEntity(Mesh& mesh, Material& material);
      EXPORT_DLL Entity& GetEntityAtIndex(const int index);

      EXPORT_DLL const Camera& GetCamera() const;
      EXPORT_DLL Camera& GetCamera();

      EXPORT_DLL void CreateTerrain();

      Scene_impl& GetImpl();

   private:
      std::unique_ptr<Scene_impl> m_impl;
   };
}