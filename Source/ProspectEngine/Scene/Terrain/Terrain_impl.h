#pragma once

#include "Include/Bitmap.h"
#include "Scene/Terrain/QuadTree.h"
#include "Renderer/Renderables/Renderable.h"

namespace Prospect
{
   class Scene_impl;

   class Terrain_impl : public Renderable
   {
   public:
      //Public
      Terrain_impl(
         const glm::vec3& origin,
         const Bitmap& heightMap,
         float size,
         float minHeight,
         float maxHeight);

      ~Terrain_impl();

      void Update(const Scene_impl& scene);

      float GetMinHeight() const;
      float GetMaxHeight() const;
      float GetSize() const;
      const std::vector<Node*>& GetEndNodes() const;
      const Bitmap& GetTerrainMap() const;

   private:
      mutable bool m_isDirty;

      Bitmap m_terrainMap;
      const float m_maxHeight;
      const float m_minHeight;
      const float m_size;

      QuadTree m_quadTree;
   };
}
