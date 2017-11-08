#pragma once

namespace Prospect
{
   class Terrain_impl;
   struct Bitmap;

   class Terrain
   {
   public:
      Terrain(
         const glm::vec3& origin,
         const Bitmap& heightMap,
         float size,
         float minHeight,
         float maxHeight);
      ~Terrain();

      Terrain(std::shared_ptr<Terrain_impl>& impl);

   private:
      std::shared_ptr<Terrain_impl> m_impl;

      friend class Scene_impl;
   };
}
