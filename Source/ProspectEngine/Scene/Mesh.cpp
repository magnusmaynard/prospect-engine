#include "Include/Mesh.h"

using namespace Prospect;
using namespace glm;

Mesh::Mesh(unsigned long id)
{
}

Mesh::Mesh(
   unsigned long id,
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices)
   :
   m_id(id),
   m_vertices(vertices),
   m_indices(indices)
{
}

const std::vector<vec3>& Mesh::GetVertices() const
{
   return m_vertices;
}

std::vector<vec3>& Mesh::GetVertices()
{
   return m_vertices;
}

const std::vector<unsigned int>& Mesh::GetIndices() const
{
   return m_indices;
}

std::vector<unsigned int>& Mesh::GetIndices()
{
   return m_indices;
}

bool Mesh::IsDirty() const
{
   return m_isDirty;
}

void Mesh::SetIsDirty(bool value) const
{
   m_isDirty = value;
}

unsigned long Mesh::GetID() const
{
   return m_id;
}
