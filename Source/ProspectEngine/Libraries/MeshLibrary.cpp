#pragma once
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

Mesh& MeshLibrary::CreatePlane(const glm::vec2& size)
{
   return m_impl->CreatePlane(size);
}
