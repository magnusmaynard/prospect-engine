#include "Include/Scene.h"
#include "Scene_impl.h"

using namespace Prospect;

Scene::Scene()
   :
   m_impl(std::make_unique<Scene_impl>(*this))
{
}

Scene::~Scene() = default;

void Scene::CreateTerrain()
{
   m_impl->CreateTerrain();
}

Entity& Scene::CreateEntity(Mesh& mesh, Material& material)
{
   return m_impl->CreateEntity(mesh, material);
}

Entity& Scene::GetEntityAtIndex(const int index)
{
   return m_impl->GetEntityAtIndex(index);
}


const Camera& Scene::GetCamera() const
{
   return m_impl->GetCamera();
}

Camera& Scene::GetCamera()
{
   return m_impl->GetCamera();
}

Scene_impl& Scene::GetImpl()
{
   return *m_impl;
}