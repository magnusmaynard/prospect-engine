#include "MeshLibrary_impl.h"

#include <vector>

using namespace Prospect;
using namespace glm;

MeshLibrary_impl::MeshLibrary_impl(MeshLibrary& parent)
   :
   m_parent(parent)
{
}

Mesh& MeshLibrary_impl::CreatePlane(const vec2& size)
{
   vec2 halfSize = size * 0.5f;

   std::vector<vec3> vertices
   {
      vec3(-halfSize.x, 0, -halfSize.y),
      vec3(-halfSize.x, 0,  halfSize.y),
      vec3(halfSize.x, 0, halfSize.y),
      vec3(halfSize.x, 0, -halfSize.y),
   };

   std::vector<unsigned int> indices =
   {
      0, 1, 2,
      0, 2, 3,
   };

   return AddMesh(vertices, indices);
}

Mesh& MeshLibrary_impl::GetMeshAtIndex(int index)
{
   if (index < 0 || index >= static_cast<int>(m_meshes.size()))
   {
      throw std::exception("No Mesh at index.");
   }

   return m_meshes[index];
}

Mesh& MeshLibrary_impl::AddMesh(
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices)
{
   m_nextMeshID++;

   m_meshes.emplace_back(Mesh(m_nextMeshID, vertices, indices));

   return m_meshes.back();
}
