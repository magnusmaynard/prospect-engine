#include "ProspectEngine_pch.h"

#include "Include/Scene.h"
#include "Scene_impl.h"

using namespace Prospect;

Scene::Scene()
   :
   m_impl(std::make_unique<Scene_impl>(*this))
{
}

Scene::~Scene() = default;

std::optional<Terrain> Scene::GetTerrain()
{
   return m_impl->GetTerrain();
}

std::optional<const Terrain> Scene::GetTerrain() const
{
   return m_impl->GetTerrain();
}

void Scene::SetTerrain(Terrain& terrain)
{
   m_impl->SetTerrain(terrain);
}

std::optional<Atmosphere> Scene::GetAtmosphere()
{
   return m_impl->GetAtmosphere();
}

std::optional<const Atmosphere> Scene::GetAtmosphere() const
{
   return m_impl->GetAtmosphere();
}

void Scene::SetAtmosphere(Atmosphere& atmosphere)
{
   m_impl->SetAtmosphere(atmosphere);
}

Entity Scene::GetEntity(const int index)
{
   return m_impl->GetEntity(index);
}

int Scene::GetEntityCount() const
{
   return m_impl->GetEntityCount();
}

void Scene::AddEntity(Entity& entity)
{
   m_impl->AddEntity(entity);
}

//Light Scene::GetLight(const int index)
//{
//   return m_impl->GetLight(index);
//}

//int Scene::GetLightCount()
//{
//   return m_impl->GetLightCount();
//}
//
//void Scene::AddLight(Light& light)
//{
//   m_impl->AddLight(light);
//}

const Camera& Scene::GetCamera() const
{
   return m_impl->GetCamera();
}

Camera& Scene::GetCamera()
{
   return m_impl->GetCamera();
}