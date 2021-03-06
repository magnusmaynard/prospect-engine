#include "ProspectEngine_pch.h"

#include "Include/Mesh.h"

#include "Scene/Mesh_impl.h"

using namespace Prospect;
using namespace glm;

Mesh::Mesh(unsigned long id)
   :
   m_impl(std::make_unique<Mesh_impl>(id))
{
}

Mesh::Mesh(
   unsigned long id,
   const std::vector<vec3>& positions,
   const std::vector<unsigned int>& indices,
   const std::vector<vec3>& normals)
   :
   m_impl(std::make_unique<Mesh_impl>(id, positions, indices, normals))
{
}

Mesh::Mesh(std::shared_ptr<Mesh_impl>& impl)
   :
   m_impl(impl)
{
}

void Mesh::Clear()
{
   m_impl->Clear();
}

Mesh::~Mesh() = default;

const std::vector<vec3>& Mesh::GetPositions() const
{
   return m_impl->GetPositions();
}

std::vector<vec3>& Mesh::GetPositions()
{
   return m_impl->GetPositions();
}

const std::vector<unsigned int>& Mesh::GetIndices() const
{
   return m_impl->GetIndices();
}

std::vector<unsigned int>& Mesh::GetIndices()
{
   return m_impl->GetIndices();
}

const std::vector<glm::vec3>& Mesh::GetNormals() const
{
   return m_impl->GetNormals();
}

std::vector<glm::vec3>& Mesh::GetNormals()
{
   return m_impl->GetNormals();
}

unsigned long Mesh::GetID() const
{
   return m_impl->GetId();
}
