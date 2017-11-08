#pragma once
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"
#include "Include/Atmosphere.h"
#include "Include/Lights/Light.h"
#include "Include/Terrain.h"

#include "Scene/Entity_impl.h"

namespace Prospect
{
   struct Bitmap;
   class Camera_impl;

   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      //Public
      void Add(Terrain& terrain);
      std::optional<Terrain> GetTerrain();

      void Add(Entity& entity);
      Entity GetEntity(const int index);

      Camera& GetCamera();
      const Camera& GetCamera() const;

      Light& AddLight(
         const glm::vec3& position,
         const glm::vec3& direction);
      Light& GetLight(const int index);

      Atmosphere* GetAtmosphere();
      const Atmosphere* GetAtmosphere() const;

      Atmosphere& CreateAtmosphere();

      //Internal
      void Update(double time);
      Entity_impl& GetRootEntity();

      Camera_impl& GetCameraImpl();
      const Camera_impl& GetCameraImpl() const;

      Terrain_impl* GetTerrainImpl();
      const Terrain_impl* GetTerrainImpl() const;

   private:
      Scene& m_parent;

      Camera m_camera;
      std::shared_ptr<Terrain_impl> m_terrain;
      std::unique_ptr<Atmosphere> m_atmosphere;
      std::deque<Light> m_lights;

      Entity_impl m_rootEntity;
   };
}
