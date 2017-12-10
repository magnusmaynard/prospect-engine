#include "ProspectEngine_pch.h"

#include "Include/MeshLibrary.h"

#include "MeshLibrary_impl.h"

using namespace Prospect;
using namespace glm;

MeshLibrary::MeshLibrary()
   :
   m_impl(std::make_unique<MeshLibrary_impl>(*this))
{
}

MeshLibrary::~MeshLibrary() = default;

Mesh MeshLibrary::CreatePlane(const vec2& size, const ivec2& sections)
{
   return m_impl->CreatePlane(size, sections);
}

Mesh MeshLibrary::CreateCube(const glm::vec3& size)
{
   return m_impl->CreateCube(size);
}

Mesh MeshLibrary::GetMeshAtIndex(int index)
{
   return m_impl->GetMeshAtIndex(index);
}

int MeshLibrary::GetMeshCount() const
{
   return m_impl->GetMeshCount();
}
