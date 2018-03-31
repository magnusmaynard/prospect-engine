#include "ProspectEngine_pch.h"

#include "Scene/Terrain/Terrain_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"

using namespace Prospect;

Terrain_impl::Terrain_impl(
   const glm::vec3& origin,
   const Bitmap& heightMap,
   float size,
   float minHeight,
   float maxHeight)
   :
   m_heightMap(heightMap),
   m_minHeight(minHeight),
   m_maxHeight(maxHeight),
   m_size(size),
   m_quadTree(glm::vec3(), m_size)
{
}

Terrain_impl::~Terrain_impl() = default;

void Terrain_impl::SetGroundTexture(const Bitmap& groundTexture)
{
   m_groundTexture = std::make_unique<Bitmap>(groundTexture);

   m_isDirty = true;
}

const Bitmap* Terrain_impl::GetGroundTexture() const
{
   return m_groundTexture.get();
}

void Terrain_impl::Update(const Scene_impl& scene)
{
   auto& camera = scene.GetCameraImpl();

   m_quadTree.Update(camera.GetPosition());
}

float Terrain_impl::GetMinHeight() const
{
   return m_minHeight;
}

float Terrain_impl::GetMaxHeight() const
{
   return m_maxHeight;
}

float Terrain_impl::GetSize() const
{
   return m_size;
}

const std::vector<Node*>& Terrain_impl::GetEndNodes() const
{
   return m_quadTree.GetEndNodes();
}

const Bitmap& Terrain_impl::GetTerrainMap() const
{
   return m_heightMap;
}
