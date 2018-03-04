#pragma once

#include <memory>
#include <optional> //TODO: Why are these needed?
#include "Lights/DirectionalLight.h"

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

   class Scene
   {
   public:
      std::optional<Terrain> GetTerrain();
      std::optional<const Terrain> GetTerrain() const;
      void SetTerrain(Terrain& terrain);

      std::optional<Atmosphere> GetAtmosphere();
      std::optional<const Atmosphere> GetAtmosphere() const;
      void SetAtmosphere(Atmosphere& atmosphere);

      Entity GetEntity(const int index);
      int GetEntityCount() const;
      void AddEntity(Entity& entity);

      //Light GetLight(const int index);
      int GetLightCount();
      void AddLight(DirectionalLight& light);

      const Camera& GetCamera() const;
      Camera& GetCamera();

   private:
      Scene();
      ~Scene();

      std::unique_ptr<Scene_impl> m_impl;

      friend class Engine_impl;
   };
}
