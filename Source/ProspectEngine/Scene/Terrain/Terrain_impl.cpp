#include "ProspectEngine_pch.h"

#include "Scene/Terrain/Terrain_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"

using namespace Prospect;

Terrain_impl::Terrain_impl(
   const glm::vec3& origin,
   const Bitmap& heightMap,
   const float size,
   const float minHeight,
   const float maxHeight)
   :
   m_heightMap(heightMap),
   m_minHeight(minHeight),
   m_maxHeight(maxHeight),
   m_size(size),
   m_quadTree(std::make_unique<QuadTree>(glm::vec3(), m_size))
{
}

Terrain_impl::~Terrain_impl()
{
}

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
   m_lodPosition = scene.GetCameraImpl().GetPosition();

   if (m_future.valid())
   {
      if (m_future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
      {
         //Work completed.
         m_quadTree = m_future.get();
      }
   }
   else if(m_quadTree->RequiresUpdate(m_lodPosition))
   {
      //Work starting.
      m_future = async(ConstructQuadTree, m_lodPosition, m_size);
   }
}

std::unique_ptr<QuadTree> Terrain_impl::ConstructQuadTree(
   const glm::vec3 cameraPosition,
   const float nodeSize)
{
   auto quadTree = std::make_unique<QuadTree>(glm::vec3(), nodeSize);
   quadTree->ForceUpdate(cameraPosition);

   return quadTree;
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
   return m_quadTree->GetEndNodes();
}

const Bitmap& Terrain_impl::GetTerrainMap() const
{
   return m_heightMap;
}

const glm::vec3 Terrain_impl::GetLodPosition() const
{
   return m_lodPosition;
}
