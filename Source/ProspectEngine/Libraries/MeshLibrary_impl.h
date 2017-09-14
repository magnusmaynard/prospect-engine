#pragma once

#include "Include/Mesh.h"
#include "Include/MeshLibrary.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "EngineDefines.h"

namespace Prospect
{
   class MeshLibrary;
   class Mesh;

   class MeshLibrary_impl
   {
   public:
      MeshLibrary_impl(MeshLibrary& parent);
      Mesh& CreatePlane(const glm::vec2& size);

      Mesh& GetMeshAtIndex(int index);

   private:
      Mesh& AddMesh(
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices);

      MeshLibrary& m_parent;

      unsigned long m_nextMeshID = DEFAULT_MESH_ID;
      std::vector<Mesh> m_meshes;
   };
}
