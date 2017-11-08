#pragma once

#include <memory>
#include <optional> //TODO: Why are these needed?

namespace Prospect
{
   class Scene_impl;

   class Terrain;
   class Mesh;
   class Material;
   class Entity;
   class Camera;
   struct Bitmap;
   class Atmosphere;
   class Light;

   class Scene
   {
   public:
      void Add(Terrain& terrain);
      std::optional<Terrain> GetTerrain();

      void Add(Entity& entity);
      Entity GetEntity(const int index);

      const Camera& GetCamera() const;
      Camera& GetCamera();

      Light& AddLight(
         const glm::vec3& position,
         const glm::vec3& direction);
      Light& GetLight(const int index);

      Atmosphere& CreateAtmosphere();

   private:
      std::unique_ptr<Scene_impl> m_impl;

      Scene();
      ~Scene();

      friend class Engine_impl;
   };
}