#pragma once

#include "Include/Mesh.h"
#include "Include/MeshLibrary.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "Defaults.h"

namespace Prospect
{
   class MeshLibrary;
   class Mesh;

   class MeshLibrary_impl
   {
   public:
      MeshLibrary_impl(MeshLibrary& parent);
      Mesh& CreatePlane(const glm::vec2& size);

   private:
      MeshLibrary& m_parent;
      Mesh& AddMesh(
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices);

      unsigned long m_nextMeshID = DEFAULT_MESH_ID;
      std::vector<Mesh> m_meshes;
   };
}
