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
   m_constructingQuadTreeMutex.unlock();
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
   auto& camera = scene.GetCameraImpl();

   if (m_quadTreeThread._Is_ready())
   {
      //Use newly constructed QuadTree.
      m_quadTree = m_quadTreeThread.get();

      //Release the mutex.
      m_constructingQuadTreeMutex.unlock();
   }

   if (m_constructingQuadTreeMutex.try_lock())
   {
      //No QuadTree is being constructed, so lock the mutex.
      if (m_quadTree->RequiresUpdate(camera.GetPosition()))
      {
         //Async begin constructing QuadTree.
         m_quadTreeThread = std::future<std::unique_ptr<QuadTree>>(async(
            ConstructQuadTree, camera.GetPosition(), m_size));
      }
   }
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

std::unique_ptr<QuadTree> Terrain_impl::ConstructQuadTree(
   const glm::vec3 cameraPosition,
   const float nodeSize)
{
   auto quadTree = std::make_unique<QuadTree>(glm::vec3(), nodeSize);
   quadTree->ForceUpdate(cameraPosition);

   return quadTree;
}
