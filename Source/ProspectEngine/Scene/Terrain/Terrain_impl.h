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

      void SetGroundTexture(const Bitmap& groundTexture);
      const Bitmap* GetGroundTexture() const;

      //Internal
      void Update(const Scene_impl& scene);

      float GetMinHeight() const;
      float GetMaxHeight() const;
      float GetSize() const;
      const std::vector<Node*>& GetEndNodes() const;
      const Bitmap& GetTerrainMap() const;

   private:
      static std::unique_ptr<QuadTree> ConstructQuadTree(const glm::vec3 cameraPosition, const float nodeSize);
      mutable bool m_isDirty;

      std::unique_ptr<Bitmap> m_groundTexture;
      Bitmap m_heightMap;
      const float m_maxHeight;
      const float m_minHeight;
      const float m_size;

      std::unique_ptr<QuadTree> m_quadTree;

      //Threading
      std::future<std::unique_ptr<QuadTree>> m_quadTreeThread;
      std::mutex m_constructingQuadTreeMutex;
   };
}
