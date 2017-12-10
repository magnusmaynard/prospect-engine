#pragma once

#include <memory>
#include "Defaults.h"

namespace Prospect
{
   class Mesh;
   class MeshLibrary_impl;

   class MeshLibrary
   {
   public:
      MeshLibrary();
      ~MeshLibrary();

      Mesh CreatePlane(
         const glm::vec2& size,
         const glm::ivec2& sections = DEFAULT_PLANE_SECTIONS);

      Mesh CreateCube(const glm::vec3& size);

      Mesh GetMeshAtIndex(int index);
      int GetMeshCount() const;

   private:
      std::unique_ptr<MeshLibrary_impl> m_impl;
   };
}
