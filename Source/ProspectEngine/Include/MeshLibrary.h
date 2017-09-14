#pragma once
#include "Defines.h"
#include <glm/vec3.hpp>
#include <memory>

namespace Prospect
{
   class Mesh;
   class MeshLibrary_impl;

   class MeshLibrary
   {
   public:
      EXPORT_DLL MeshLibrary();
      EXPORT_DLL ~MeshLibrary();

      EXPORT_DLL Mesh& CreatePlane(const glm::vec2& size);
      EXPORT_DLL Mesh& GetMeshAtIndex(int index);

   private:
      std::unique_ptr<MeshLibrary_impl> m_impl;
   };
}
