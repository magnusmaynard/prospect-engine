#include "Include/Mesh.h"

using namespace Prospect;
using namespace glm;

Mesh::Mesh(
   const std::vector<vec3>& points,
   const std::vector<int>& indices)
   :
   m_points(points),
   m_indices(indices)
{
}

Mesh::Mesh(
   const std::vector<vec3>& points,
   const std::vector<int>& indices,
   const std::vector<vec3>& normals)
   :
   m_points(points),
   m_indices(indices),
   m_normals(normals)
{
}

Mesh Mesh::CreatePlane(
   const vec3& position,
   const vec2& size)
{
   vec2 halfSize = size * 0.5f;

   std::vector<vec3> points
   {
      position + vec3(-halfSize.x, -halfSize.y, 0),
      position + vec3(-halfSize.x,  halfSize.y, 0),
      position + vec3(halfSize.x,  halfSize.y, 0),
      position + vec3(halfSize.x, -halfSize.y, 0),
   };

   std::vector<int> indices =
   {
      0, 1, 2,
      0, 2, 3,
   };

   return Mesh(points, indices);
}

//Mesh Mesh::CreateBox(const vec3& position, const vec3& size)
//{
//   vec3 halfSize = size * 0.5f;
//   std::vector<vec3> points;
//
//   points.push_back(position + vec3(-halfSize.x, -halfSize.y, -halfSize.z));
//   points.push_back(position + vec3(-halfSize.x,  halfSize.y, -halfSize.z));
//   points.push_back(position + vec3( halfSize.x,  halfSize.y, -halfSize.z));
//   points.push_back(position + vec3( halfSize.x, -halfSize.y, -halfSize.z));
//
//   points.push_back(position + vec3(-halfSize.x, -halfSize.y, -halfSize.z));
//   points.push_back(position + vec3(-halfSize.x,  halfSize.y, -halfSize.z));
//   points.push_back(position + vec3( halfSize.x,  halfSize.y, -halfSize.z));
//   points.push_back(position + vec3( halfSize.x, -halfSize.y, -halfSize.z));
//
//
//   std::vector<int> indices;
//}
