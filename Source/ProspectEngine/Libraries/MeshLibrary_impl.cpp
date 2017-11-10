#include "ProspectEngine_pch.h"

#include "MeshLibrary_impl.h"

using namespace Prospect;
using namespace glm;

MeshLibrary_impl::MeshLibrary_impl(MeshLibrary& parent)
   : m_parent(parent)
{
}

Mesh& MeshLibrary_impl::CreatePlane(const vec2& size)
{
   const vec2 halfSize = size * 0.5f;

   const std::vector<vec3> vertices
   {
      vec3(-halfSize.x, 0, -halfSize.y),
      vec3(-halfSize.x, 0, halfSize.y),
      vec3(halfSize.x, 0, halfSize.y),
      vec3(halfSize.x, 0, -halfSize.y),
   };

   static const std::vector<unsigned int> indices =
   {
      0, 1, 2,
      0, 2, 3,
   };

   static const std::vector<vec3> normals =
   {
      vec3(0, 1, 0),
      vec3(0, 1, 0),
      vec3(0, 1, 0),
      vec3(0, 1, 0),
   };

   return AddMesh(vertices, indices, normals);
}

Mesh& MeshLibrary_impl::CreateCube(const vec3& size)
{
   const vec3 halfSize = size * 0.5f;

   const std::vector<vec3> vertices =
   {
      { -halfSize.x, -halfSize.y, -halfSize.z },
      { halfSize.x, -halfSize.y, -halfSize.z },
      { halfSize.x, halfSize.y, -halfSize.z },
      { -halfSize.x, halfSize.y, -halfSize.z },
      { -halfSize.x, -halfSize.y, halfSize.z },
      { halfSize.x, -halfSize.y, halfSize.z },
      { halfSize.x, halfSize.y, halfSize.z },
      { -halfSize.x, halfSize.y, halfSize.z },
   };

   static const std::vector<unsigned int> indices =
   {
      0, 1, 3, 3, 1, 2,
      1, 5, 2, 2, 5, 6,
      5, 4, 6, 6, 4, 7,
      4, 0, 7, 7, 0, 3,
      3, 2, 7, 7, 2, 6,
      4, 5, 0, 0, 5, 1
   };

   //TODO: Calculate normals.
   static const std::vector<vec3> normals =
   {
      { 0, 0, 1 },
      { 1, 0, 0 },
      { 0, 0, -1 },
      { -1, 0, 0 },
      { 0, 1, 0 },
      { 0, -1, 0 }
   };

   return AddMesh(vertices, indices, normals);
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
   const std::vector<unsigned int>& indices,
   const std::vector<vec3>& normals)
{
   m_nextMeshID++;

   m_meshes.emplace_back(Mesh(m_nextMeshID, vertices, indices, normals));

   return m_meshes.back();
}
