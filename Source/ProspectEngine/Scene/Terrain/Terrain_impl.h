#pragma once

#include "Include/Image.h"
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
         const Image& heightMap,
         float size,
         float minHeight,
         float maxHeight);

      ~Terrain_impl();

      void SetGroundTexture(const Image& groundTexture);
      const Image* GetGroundTexture() const;

      //Internal
      void Update(const Scene_impl& scene);

      float GetMinHeight() const;
      float GetMaxHeight() const;
      float GetSize() const;
      const std::vector<Node*>& GetEndNodes() const;
      const Image& GetTerrainMap() const;

   private:
      mutable bool m_isDirty;

      std::unique_ptr<Image> m_groundTexture;
      Image m_heightMap;
      const float m_maxHeight;
      const float m_minHeight;
      const float m_size;

      QuadTree m_quadTree;
   };
}
