#include "ProspectEngine_pch.h"

#include "Scene/Mesh_impl.h"

#include "Include/Mesh.h"

using namespace Prospect;
using namespace glm;

Mesh_impl::Mesh_impl(unsigned long id)
   :
   m_id(id)
{
}

Mesh_impl::Mesh_impl(
   unsigned long id,
   const std::vector<vec3>& positions,
   const std::vector<unsigned int>& indices,
   const std::vector<vec3>& normals)
   :
   m_id(id),
   m_positions(positions),
   m_indices(indices),
   m_normals(normals)
{
}

void Mesh_impl::Clear()
{
   m_positions.clear();
   m_indices.clear();
   m_normals.clear();
}

const std::vector<vec3>& Mesh_impl::GetPositions() const
{
   return m_positions;
}

std::vector<vec3>& Mesh_impl::GetPositions()
{
   return m_positions;
}

const std::vector<unsigned int>& Mesh_impl::GetIndices() const
{
   return m_indices;
}

std::vector<unsigned int>& Mesh_impl::GetIndices()
{
   return m_indices;
}

const std::vector<glm::vec3>& Mesh_impl::GetNormals() const
{
   return m_normals;
}

std::vector<glm::vec3>& Mesh_impl::GetNormals()
{
   return m_normals;
}

bool Mesh_impl::IsDirty() const
{
   return m_isDirty;
}

void Mesh_impl::SetIsDirty(bool value) const
{
   m_isDirty = value;
}

unsigned long Mesh_impl::GetId() const
{
   return m_id;
}
