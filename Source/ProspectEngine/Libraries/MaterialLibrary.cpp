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

Material MaterialLibrary::CreateMaterial(
   const Color& diffuse,
   const Color& ambient,
   const Color& specular,
   float specularPower)
{
   return m_impl->CreateMaterial(diffuse, ambient, specular, specularPower);
}

Material MaterialLibrary::GetMaterialAtIndex(int index)
{
   return m_impl->GetMaterialAtIndex(index);
}

int MaterialLibrary::GetMaterialCount() const
{
   return m_impl->GetMaterialCount();
}
