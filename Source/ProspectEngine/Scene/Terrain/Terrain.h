#pragma once

#include "Include/Bitmap.h"
#include "Scene/Terrain/QuadTree.h"

namespace Prospect
{
   class Scene_impl;

   class Terrain
   {
   public:
      Terrain(
         const glm::vec3& origin,
         const Bitmap& heightMap,
         float size,
         float minHeight,
         float maxHeight);

      void Update(const Scene_impl& scene);

      float GetMinHeight() const;
      float GetMaxHeight() const;
      float GetSize() const;
      const std::vector<Node*>& GetEndNodes() const;
      const Bitmap& GetTerrainMap() const;

   private:
      Bitmap m_terrainMap;
      const float m_maxHeight;
      const float m_minHeight;
      const float m_size;

      QuadTree m_quadTree;
   };
}
