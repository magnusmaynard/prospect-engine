#pragma once
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"

#include "Libraries/EntityLibrary.h"
#include "Scene/Terrain/Terrain.h"

namespace Prospect
{
   struct Bitmap;
   class Camera_impl;

   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      //Public
      Camera& GetCamera();
      const Camera& GetCamera() const;

      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntity(const int index);

      void CreateTerrain(
         const glm::vec3& origin,
         const Bitmap& heightMap,
         float size,
         float minHeight,
         float maxHeight);

      void CreateAtmosphere();

      //Internal
      void Update(double time);
      Entity* GetRootEntity();
      EntityLibrary& GetEntityLib();

      Camera_impl& GetCameraImpl();
      const Camera_impl& GetCameraImpl() const;

      const Terrain* GetTerrain() const;

   private:
      Scene& m_parent;

      Camera m_camera;
      std::unique_ptr<Terrain> m_terrain;

      EntityLibrary m_entityLib;
      Entity* m_rootEntity;
   };
}
