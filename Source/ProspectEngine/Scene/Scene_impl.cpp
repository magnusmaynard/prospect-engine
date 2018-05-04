#include "ProspectEngine_pch.h"

#include "Scene/Scene_impl.h"

#include "Engine/EngineDefines.h"
#include "Engine/Extensions.h"
#include "Scene/Terrain/Terrain_impl.h"
#include "Include/Lights/DirectionalLight.h"
#include "Scene/Lights/DirectionalLight_impl.h"

using namespace Prospect;
using namespace glm;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent),
   m_camera(Defaults::CAMERA_SIZE)
{
}

std::optional<Atmosphere> Scene_impl::GetAtmosphere()
{
   return MakeOptionalImpl<Atmosphere>(m_atmosphere);
}

void Scene_impl::SetAtmosphere(Atmosphere& atmosphere)
{
   m_atmosphere = atmosphere.m_impl;
}

std::optional<Terrain> Scene_impl::GetTerrain()
{
   return MakeOptionalImpl<Terrain>(m_terrain);
}

void Scene_impl::SetTerrain(Terrain& terrain)
{
   m_terrain = terrain.m_impl;
}

Entity Scene_impl::GetEntity(const int index)
{
   return m_rootEntity.GetEntity(index);
}

void Scene_impl::AddEntity(Entity& entity)
{
   m_rootEntity.AddEntity(entity);
}

int Scene_impl::GetEntityCount() const
{
   return m_rootEntity.GetEntityCount();
}

//Light Scene_impl::GetLight(const int index)
//{
//   if (index < 0 || index >= static_cast<int>(m_lights.size()))
//   {
//      throw std::exception("No Light at index.");
//   }
//
//   return m_lights[index];
//}

//Light_impl* Scene_impl::GetLightImpl(const int index)
//{
//   return const_cast<Light_impl*>(static_cast<const Scene_impl*>(this)->GetLightImpl(index));
//}
//
//const Light_impl* Scene_impl::GetLightImpl(const int index) const
//{
//   if (index < 0 || index >= static_cast<int>(m_lights.size()))
//   {
//      throw std::exception("No Light at index.");
//   }
//
//   return m_lights[index].get();
//}

int Scene_impl::GetLightCount() const
{
   return m_lights.size();
}

void Scene_impl::AddLight(DirectionalLight& light)
{
   //TODO: does this work?
   m_lights.push_back(std::dynamic_pointer_cast<ILight_impl>(light.m_impl));
}

Camera& Scene_impl::GetCamera()
{
   return m_camera;
}

void Scene_impl::Update(double time)
{
   const mat4 origin;
   m_rootEntity.UpdateTransformMatrix(origin, false);

   if (m_terrain)
   {
      m_terrain->Update(*this);
   }
}

Entity_impl& Scene_impl::GetRootEntityImpl()
{
   return m_rootEntity;
}

Atmosphere_impl* Scene_impl::GetAtmosphereImpl()
{
   return m_atmosphere.get();
}

const Atmosphere_impl* Scene_impl::GetAtmosphereImpl() const
{
   return m_atmosphere.get();
}

Terrain_impl* Scene_impl::GetTerrainImpl()
{
   if (!m_terrain)
   {
      return nullptr;
   }
   
   return m_terrain.get();
}

const Terrain_impl* Scene_impl::GetTerrainImpl() const
{
   if (!m_terrain)
   {
      return nullptr;
   }

   return m_terrain.get();
}

Camera_impl& Scene_impl::GetCameraImpl()
{
   return *m_camera.m_impl;
}

const Camera_impl& Scene_impl::GetCameraImpl() const
{
   return *m_camera.m_impl;
}

const std::deque<std::shared_ptr<ILight_impl>>& Scene_impl::GetLights() const
{
   return m_lights;
}

ILight_impl* Scene_impl::GetLightImpl(const int index)
{
   return m_lights[index].get();
}

const ILight_impl* Scene_impl::GetLightImpl(const int index) const
{
   return m_lights[index].get();
}
