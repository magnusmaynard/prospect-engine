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

Material MaterialLibrary::CreateMaterial()
{
   return m_impl->CreateMaterial();
}

Material MaterialLibrary::CreateMaterial(const Color& diffuse)
{
   return m_impl->CreateMaterial(diffuse);
}

Material MaterialLibrary::CreateMaterial(
   const Color& diffuse,
   const Color& ambient,
   const Color& specular,
   const float specularPower)
{
   return m_impl->CreateMaterial(diffuse, ambient, specular, specularPower);
}

Material MaterialLibrary::GetMaterialAtIndex(const int index)
{
   return m_impl->GetMaterialAtIndex(index);
}

int MaterialLibrary::GetMaterialCount() const
{
   return m_impl->GetMaterialCount();
}
