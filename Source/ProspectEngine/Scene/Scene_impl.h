#pragma once
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"
#include "Include/Atmosphere.h"
#include "Include/Terrain.h"

#include "Scene/Entity_impl.h"
#include "Scene/Lights/ILight_impl.h"

namespace Prospect
{
   struct Bitmap;
   class Camera_impl;

   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      //Public
      std::optional<Atmosphere> GetAtmosphere();
      void SetAtmosphere(Atmosphere& atmosphere);

      std::optional<Terrain> GetTerrain();
      void SetTerrain(Terrain& terrain);

      void AddEntity(Entity& entity);
      int GetEntityCount() const;
      Entity GetEntity(const int index);

      //Light GetLight(const int index);
      int GetLightCount() const;
      void AddLight(DirectionalLight& light);

      Camera& GetCamera();

      //Internal
      void Update(double time);
      Entity_impl& GetRootEntityImpl();

      Atmosphere_impl* GetAtmosphereImpl();
      const Atmosphere_impl* GetAtmosphereImpl() const;

      Terrain_impl* GetTerrainImpl();
      const Terrain_impl* GetTerrainImpl() const;

      Camera_impl& GetCameraImpl();
      const Camera_impl& GetCameraImpl() const;

      std::deque<std::shared_ptr<ILight_impl>> GetLights() const;
      const ILight_impl* GetLightImpl(const int index) const;
      ILight_impl* GetLightImpl(const int index);

   private:
      Scene& m_parent;

      Camera m_camera;
      std::shared_ptr<Terrain_impl> m_terrain;
      std::shared_ptr<Atmosphere_impl> m_atmosphere;
      std::deque<std::shared_ptr<ILight_impl>> m_lights;

      Entity_impl m_rootEntity;
   };
}
