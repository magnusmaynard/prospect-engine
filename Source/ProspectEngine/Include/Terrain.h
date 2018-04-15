#pragma once

namespace Prospect
{
   class Terrain_impl;
   struct Image;

   class Terrain
   {
   public:
      Terrain(
         const glm::vec3& origin,
         const Image& heightMap,
         float size,
         float minHeight,
         float maxHeight);
      ~Terrain();

      Terrain(std::shared_ptr<Terrain_impl>& impl);

      void SetGroundTexture(const Image& groundTexture);

   private:
      std::shared_ptr<Terrain_impl> m_impl;

      friend class Scene_impl;
   };
}
