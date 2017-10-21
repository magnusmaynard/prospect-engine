#include "ProspectEngine_pch.h"

#include "Terrain.h"
#include "Scene/Scene_impl.h"

using namespace Prospect;

Terrain::Terrain(
   const glm::vec3& origin,
   const Bitmap& heightMap,
   float size,
   float minHeight,
   float maxHeight)
   :
   m_terrainMap(heightMap),
   m_minHeight(minHeight),
   m_maxHeight(maxHeight),
   m_size(size),
   m_quadTree(glm::vec3(), m_size)
{
}

void Terrain::Update(const Scene_impl& scene)
{
   auto& camera = scene.GetCamera();

   m_quadTree.Update(camera.GetPosition());
}

float Terrain::GetMinHeight() const
{
   return m_minHeight;
}

float Terrain::GetMaxHeight() const
{
   return m_maxHeight;
}

float Terrain::GetSize() const
{
   return m_size;
}

const std::vector<Node*>& Terrain::GetEndNodes() const
{
   return m_quadTree.GetEndNodes();
}

const Bitmap& Terrain::GetTerrainMap() const
{
   return m_terrainMap;
}
