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

Entity& Scene::AddEntity()
{
   return m_impl->AddEntity();
}

Entity& Scene::GetEntity(const int index)
{
   return m_impl->GetEntity(index);
}

Scene_impl& Scene::GetImpl()
{
   return *m_impl;
}