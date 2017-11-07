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

void Scene::Add(Terrain& terrain)
{
   m_impl->Add(terrain);
}

std::optional<Terrain> Scene::GetTerrain()
{
   return m_impl->GetTerrain();
}

Entity& Scene::AddEntity(Mesh* mesh, Material* material)
{
   return m_impl->AddEntity(mesh, material);
}

Entity& Scene::GetEntity(const int index)
{
   return m_impl->GetEntity(index);
}

const Camera& Scene::GetCamera() const
{
   return m_impl->GetCamera();
}

Camera& Scene::GetCamera()
{
   return m_impl->GetCamera();
}

Light& Scene::AddLight(
   const glm::vec3& position,
   const glm::vec3& direction)
{
   return m_impl->AddLight(position, direction);
}

Light& Scene::GetLight(const int index)
{
   return m_impl->GetLight(index);
}

Atmosphere& Scene::CreateAtmosphere()
{
   return m_impl->CreateAtmosphere();
}
