#include "Include/Mesh.h"

using namespace Prospect;
using namespace glm;

Mesh::Mesh()
{
}

Mesh::Mesh(
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices)
   :
   m_vertices(vertices),
   m_indices(indices)
{
}

Mesh::Mesh(
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices,
   const std::vector<vec3>& normals)
   :
   m_vertices(vertices),
   m_indices(indices),
   m_normals(normals)
{
}

std::vector<vec3>& Mesh::GetVertices()
{
   return m_vertices;
}

std::vector<unsigned int>& Mesh::GetIndices()
{
   return m_indices;
}


bool Mesh::IsDirty() const
{
   return m_isDirty;
}

void Mesh::SetIsDirty(bool value)
{
   m_isDirty = value;
}



Mesh Mesh::CreatePlane(
   const vec3& origin,
   const vec2& size)
{
   vec2 halfSize = size * 0.5f;

   std::vector<vec3> points
   {
      origin + vec3(-halfSize.x, -halfSize.y, 0),
      origin + vec3(-halfSize.x,  halfSize.y, 0),
      origin + vec3(halfSize.x,  halfSize.y, 0),
      origin + vec3(halfSize.x, -halfSize.y, 0),
   };

   std::vector<unsigned int> indices =
   {
      0, 2, 1, //0,1,2
      0, 2, 3,
   };

   return Mesh(points, indices);
}
