#include "ProspectEngine_pch.h"

#include "Scene/Scene_impl.h"

#include "EngineDefines.h"
#include "Scene/Entity_impl.h"
#include "Scene/Terrain/Terrain_impl.h"

using namespace Prospect;
using namespace glm;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent),
   m_camera(DEFAULT_CAMERA_SIZE)
{
   m_rootEntity = &m_entityLib.AddEntity(nullptr, nullptr, nullptr);
}

void Scene_impl::Add(Terrain& terrain)
{
   m_terrain = terrain.m_impl;
}

std::optional<Terrain> Scene_impl::GetTerrain()
{
   return m_terrain ? std::optional<Terrain>(m_terrain) : std::nullopt;
}

Camera& Scene_impl::GetCamera()
{
   return m_camera;
}

const Camera& Scene_impl::GetCamera() const
{
   return m_camera;
}

Light& Scene_impl::AddLight(
   const vec3& position,
   const vec3& direction)
{
   m_lights.push_back(Light(position, direction));

   return m_lights.back();
}

Light& Scene_impl::GetLight(const int index)
{
   if (index < 0 || index >= static_cast<int>(m_lights.size()))
   {
      throw std::exception("No Light at index.");
   }

   return m_lights[index];
}

Atmosphere* Scene_impl::GetAtmosphere()
{
   return m_atmosphere.get();
}

const Atmosphere* Scene_impl::GetAtmosphere() const
{
   return m_atmosphere.get();
}

Entity& Scene_impl::AddEntity(Mesh* mesh, Material* material)
{
   return m_rootEntity->AddEntity(mesh, material);
}

Entity& Scene_impl::GetEntity(const int index)
{
   return m_rootEntity->GetEntity(index);
}

Atmosphere& Scene_impl::CreateAtmosphere()
{
   m_atmosphere = std::make_unique<Atmosphere>();

   return *m_atmosphere.get();
}

void Scene_impl::Update(double time)
{
   mat4 origin;
   m_rootEntity->m_impl->UpdateTransform(origin, false);

   if (m_terrain)
   {
      m_terrain->Update(*this);
   }
}

Entity* Scene_impl::GetRootEntity()
{
   return m_rootEntity;
}

Camera_impl& Scene_impl::GetCameraImpl()
{
   return *m_camera.m_impl;
}

const Camera_impl& Scene_impl::GetCameraImpl() const
{
   return *m_camera.m_impl;
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

EntityLibrary& Scene_impl::GetEntityLib()
{
   return m_entityLib;
}
