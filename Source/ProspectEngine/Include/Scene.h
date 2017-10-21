#pragma once

#include <memory>

namespace Prospect
{
   class Scene_impl;

   class Mesh;
   class Material;
   class Entity;
   class Camera;
   struct Bitmap;

   class Scene
   {
   public:
      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntity(const int index);

      const Camera& GetCamera() const;
      Camera& GetCamera();

      void CreateTerrain(
         const glm::vec3& origin,
         const Bitmap& heightMap,
         float size,
         float minHeight,
         float maxHeight);

      void CreateAtmosphere();

   private:
      std::unique_ptr<Scene_impl> m_impl;

      Scene();
      ~Scene();

      friend class Engine_impl;
   };
}