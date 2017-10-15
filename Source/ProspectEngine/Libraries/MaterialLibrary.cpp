#include "ProspectEngine_pch.h"

#include "Include/MaterialLibrary.h"

#include "MaterialLibrary_impl.h"

using namespace Prospect;

MaterialLibrary::MaterialLibrary()
   :
   m_impl(std::make_unique<MaterialLibrary_impl>(*this))
{
}

MaterialLibrary::~MaterialLibrary() = default;

Material& MaterialLibrary::CreateMaterial(const Color& color)
{
   return m_impl->CreateMaterial(color);
}

Material& MaterialLibrary::GetMaterialAtIndex(int index)
{
   return m_impl->GetMaterialAtIndex(index);
}