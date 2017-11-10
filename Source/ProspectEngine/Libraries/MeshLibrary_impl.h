#pragma once

#include "Include/Mesh.h"
#include "Include/MeshLibrary.h"

#include <vector>
#include <deque>
#include "Engine/EngineDefines.h"

namespace Prospect
{
   class MeshLibrary;

   class MeshLibrary_impl
   {
   public:
      MeshLibrary_impl(MeshLibrary& parent);
      Mesh& CreatePlane(const glm::vec2& size);
      Mesh& CreateCube(const glm::vec3& size);

      Mesh& GetMeshAtIndex(int index);

   private:
      Mesh& AddMesh(
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<glm::vec3>& normals);

      MeshLibrary& m_parent;

      unsigned long m_nextMeshID = NULL_ID;
      std::deque<Mesh> m_meshes;
   };
}
