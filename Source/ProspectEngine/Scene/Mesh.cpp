#include "Include/Mesh.h"

#include "Mesh_impl.h"

using namespace Prospect;
using namespace glm;

Mesh::Mesh(unsigned long id)
   :
   m_impl(std::make_unique<Mesh_impl>(*this, id))
{
}

Mesh::Mesh(
   unsigned long id,
   const std::vector<vec3>& vertices,
   const std::vector<unsigned int>& indices)
   :
   m_impl(std::make_unique<Mesh_impl>(*this, id, vertices, indices))
{
}

Mesh::~Mesh() = default;
Mesh::Mesh(Mesh&& other) = default;
Mesh& Mesh::operator=(Mesh&& other) = default;

const std::vector<vec3>& Mesh::GetVertices() const
{
   return m_impl->GetVertices();
}

std::vector<vec3>& Mesh::GetVertices()
{
   return m_impl->GetVertices();
}

const std::vector<unsigned int>& Mesh::GetIndices() const
{
   return m_impl->GetIndices();
}

std::vector<unsigned int>& Mesh::GetIndices()
{
   return m_impl->GetIndices();
}

unsigned long Mesh::GetID() const
{
   return m_impl->GetID();
}
