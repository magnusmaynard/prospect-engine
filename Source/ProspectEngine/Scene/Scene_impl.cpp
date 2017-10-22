#include "ProspectEngine_pch.h"

#include "Scene/Scene_impl.h"

#include "EngineDefines.h"
#include "Scene/Entity_impl.h"

using namespace Prospect;
using namespace glm;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent),
   m_camera(DEFAULT_CAMERA_SIZE)
{
   m_rootEntity = &m_entityLib.AddEntity(nullptr, nullptr, nullptr);
}

Camera& Scene_impl::GetCamera()
{
   return m_camera;
}

const Camera& Scene_impl::GetCamera() const
{
   return m_camera;
}

Entity& Scene_impl::AddEntity(Mesh* mesh, Material* material)
{
   return m_rootEntity->AddEntity(mesh, material);
}

Entity& Scene_impl::GetEntity(const int index)
{
   return m_rootEntity->GetEntity(index);
}

void Scene_impl::CreateTerrain(
   const vec3& origin,
   const Bitmap& heightMap,
   float size,
   float minHeight,
   float maxHeight)
{
   m_terrain = std::make_unique<Terrain>(
      origin,
      heightMap,
      size,
      minHeight,
      maxHeight);
}

void Scene_impl::CreateAtmosphere()
{
   //TODO:
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

EntityLibrary& Scene_impl::GetEntityLib()
{
   return m_entityLib;
}

const Terrain* Scene_impl::GetTerrain() const
{
   return m_terrain.get();
}
