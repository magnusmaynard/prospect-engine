#pragma once

#include <glm/vec3.hpp>
#include <memory>

namespace Prospect
{
   class Mesh;
   class MeshLibrary_impl;

   class MeshLibrary
   {
   public:
      MeshLibrary();
      ~MeshLibrary();

      Mesh& CreatePlane(const glm::vec2& size);
      Mesh& GetMeshAtIndex(int index);

   private:
      std::unique_ptr<MeshLibrary_impl> m_impl;
   };
}
