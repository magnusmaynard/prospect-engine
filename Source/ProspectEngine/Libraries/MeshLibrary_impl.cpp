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

Mesh MeshLibrary_impl::CreateEmpty()
{
   return AddMesh({}, {}, {});
}

Mesh MeshLibrary_impl::CreatePlane(const vec2& size, const ivec2& sections)
{
   std::vector<vec3> vertices;
   std::vector<unsigned int> indices;
   std::vector<vec3> normals;

   static const int VERTICES_PER_SECTION = 4;
   static const int INDICES_PER_SECTION = 6;

   const vec3 origin(0, 0, 0);
   const vec3 offset = origin - vec3(size.x, 0, size.y) * 0.5f;
   const vec2 sectionSize(size.x / sections.x, size.y / sections.y);

   vertices.reserve(sections.x * sections.y * VERTICES_PER_SECTION);
   vertices.reserve(sections.x * sections.y * INDICES_PER_SECTION);

   for(int y = 0; y < sections.y; y++)
   {
      for (int x = 0; x < sections.x; x++)
      {
         //Verticies
         vertices.push_back({ offset.x + sectionSize.x * (x + 0), offset.y, offset.z + sectionSize.y * (y + 0) });
         vertices.push_back({ offset.x + sectionSize.x * (x + 0), offset.y, offset.z + sectionSize.y * (y + 1) });
         vertices.push_back({ offset.x + sectionSize.x * (x + 1), offset.y, offset.z + sectionSize.y * (y + 1) });
         vertices.push_back({ offset.x + sectionSize.x * (x + 1), offset.y, offset.z + sectionSize.y * (y + 0) });

         //Indices
         const int baseIndex = x * VERTICES_PER_SECTION + y * sections.x * VERTICES_PER_SECTION;
         indices.push_back(baseIndex + 0);
         indices.push_back(baseIndex + 1);
         indices.push_back(baseIndex + 2);
         indices.push_back(baseIndex + 0);
         indices.push_back(baseIndex + 2);
         indices.push_back(baseIndex + 3);
      }
   }

   //Normals
   normals.resize(vertices.size(), { 0, 1, 0 });

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

Mesh MeshLibrary_impl::GetMeshAtIndex(const int index)
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
