#include "Scene_impl.h"

using namespace Prospect;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent),
   m_camera(DEFAULT_CAMERA_SIZE)
{
   //Reserve so adding new entities does not invalidate references to them.
   m_entities.reserve(MAX_ENTITIES);
}

void Scene_impl::CreateTerrain()
{
   m_terrain = std::make_unique<Terrain>();
}

Camera& Scene_impl::GetCamera()
{
   return m_camera;
}

const Camera& Scene_impl::GetCamera() const
{
   return m_camera;
}

Terrain* Scene_impl::GetTerrain()
{
   return m_terrain.get();
}

const Terrain* Scene_impl::GetTerrain() const
{
   return m_terrain.get();
}

Entity& Scene_impl::CreateEntity(Mesh& mesh, Material& material)
{
   m_nextEntityID++;

   m_entities.emplace_back(Entity(m_nextEntityID, mesh, material));

   return m_entities.back();
}

Entity& Scene_impl::GetEntityAtIndex(const int index)
{
   if(index < 0 || index >= static_cast<int>(m_entities.size()))
   {
      throw std::exception("No Entity at index.");
   }

   return m_entities[index];
}

std::vector<Entity>& Scene_impl::GetEntities()
{
   return m_entities;
}
