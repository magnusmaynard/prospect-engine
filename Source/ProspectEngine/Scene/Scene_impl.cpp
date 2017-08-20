#include "Scene_impl.h"

using namespace Prospect;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent)
{
}

void Scene_impl::CreateCamera(const glm::ivec2& size)
{
   m_camera = std::make_unique<Camera>(size);
}

void Scene_impl::CreateTerrain()
{
   m_terrain = std::make_unique<Terrain>();
}

Camera* Scene_impl::GetCamera()
{
   return m_camera.get();
}

const Camera* Scene_impl::GetCamera() const
{
   return m_camera.get();
}

Terrain* Scene_impl::GetTerrain()
{
   return m_terrain.get();
}

const Terrain* Scene_impl::GetTerrain() const
{
   return m_terrain.get();
}

