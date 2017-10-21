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

void Scene::CreateTerrain(
   const glm::vec3& origin,
   const Bitmap& heightMap,
   float size,
   float minHeight,
   float maxHeight)
{
   m_impl->CreateTerrain(
      origin,
      heightMap,
      size,
      minHeight,
      maxHeight);
}

void Scene::CreateAtmosphere()
{
   m_impl->CreateAtmosphere();
}
