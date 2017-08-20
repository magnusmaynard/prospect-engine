#include "Include/Scene.h"
#include "Scene_impl.h"

using namespace Prospect;

Scene::Scene()
   :
   m_impl(std::make_unique<Scene_impl>(*this))
{
}

Scene::~Scene() = default;

Scene_impl& Scene::GetImpl()
{
   return *m_impl;
}

const Scene_impl& Scene::GetImpl() const
{
   return *m_impl;
}

void Scene::CreateTerrain()
{
   m_impl->CreateTerrain();
}

