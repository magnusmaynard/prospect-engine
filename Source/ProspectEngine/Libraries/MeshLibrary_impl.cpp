#include "ProspectEngine_pch.h"

#include "MeshLibrary_impl.h"

#include "Scene/Mesh_impl.h"

using namespace Prospect;
using namespace glm;

MeshLibrary_impl::MeshLibrary_impl(MeshLibrary& parent)
   :
   m_parent(parent),
   m_nextMeshID(0)
{
}

Mesh MeshLibrary_impl::CreatePlane(const vec2& size)
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

Mesh MeshLibrary_impl::CreateCube(const vec3& size)
{
   const vec3 s = size * 0.5f;

   const std::vector<vec3> vertices =
   {
      //Top
      { -s.x, +s.y, +s.z },
      { -s.x, +s.y, -s.z },
      { +s.x, +s.y, -s.z },
      { +s.x, +s.y, +s.z },
      //Bottom
      { -s.x, -s.y, +s.z },
      { -s.x, -s.y, -s.z },
      { +s.x, -s.y, -s.z },
      { +s.x, -s.y, +s.z },
      //Left
      { -s.x, +s.y, +s.z },
      { -s.x, +s.y, -s.z },
      { -s.x, -s.y, -s.z },
      { -s.x, -s.y, +s.z },
      //Right
      { +s.x, +s.y, +s.z },
      { +s.x, +s.y, -s.z },
      { +s.x, -s.y, -s.z },
      { +s.x, -s.y, +s.z },
      //Front
      { -s.x, +s.y, +s.z },
      { +s.x, +s.y, +s.z },
      { +s.x, -s.y, +s.z },
      { -s.x, -s.y, +s.z },
      //Back
      { -s.x, +s.y, -s.z },
      { +s.x, +s.y, -s.z },
      { +s.x, -s.y, -s.z },
      { -s.x, -s.y, -s.z },
   };

   static const std::vector<unsigned int> indices =
   {
      //Top
      0, 3, 2,
      0, 2, 1,
      //Bottom
      4, 6, 7,
      4, 5, 6,
      //Left
      8, 9, 10,
      8, 10, 11,
      //Right
      12, 14, 13,
      12, 15, 14,
      //Front
      16, 19, 18,
      16, 18, 17,
      //Back
      20, 22, 23,
      20, 21, 22,
   };

   static const std::vector<vec3> normals =
   {
      //Top
      { 0, +1, 0 },
      { 0, +1, 0 },
      { 0, +1, 0 },
      { 0, +1, 0 },
      //Bottom
      { 0, -1, 0 },
      { 0, -1, 0 },
      { 0, -1, 0 },
      { 0, -1, 0 },
      //Left
      { -1, 0, 0 },
      { -1, 0, 0 },
      { -1, 0, 0 },
      { -1, 0, 0 },
      //Right
      { +1, 0, 0 },
      { +1, 0, 0 },
      { +1, 0, 0 },
      { +1, 0, 0 },
      //Front
      { 0, 0, +1 },
      { 0, 0, +1 },
      { 0, 0, +1 },
      { 0, 0, +1 },
      //Back
      { 0, 0, -1 },
      { 0, 0, -1 },
      { 0, 0, -1 },
      { 0, 0, -1 },
   };

   return AddMesh(vertices, indices, normals);
}


Mesh MeshLibrary_impl::GetMeshAtIndex(int index)
{
   if (index < 0 || index >= static_cast<int>(m_meshes.size()))
   {
      throw std::exception("No Mesh at index.");
   }

   return m_meshes[index];
}

int MeshLibrary_impl::GetMeshCount() const
{
   return m_meshes.size();
}

Mesh MeshLibrary_impl::AddMesh(
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices,
   const std::vector<vec3>& normals)
{
   m_meshes.emplace_back(std::make_shared<Mesh_impl>(m_nextMeshID, vertices, indices, normals));

   m_nextMeshID++;

   return m_meshes.back();
}
