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
   const Color& emissive,
   const Color& specular,
   const int specularPower)
{
   return m_impl->CreateMaterial(diffuse, emissive, specular, specularPower);
}

Material MaterialLibrary::GetMaterial(const int index)
{
   return m_impl->GetMaterial(index);
}

int MaterialLibrary::GetMaterialCount() const
{
   return m_impl->GetMaterialCount();
}

MaterialLibrary_impl& MaterialLibrary::GetImpl()
{
   return *m_impl.get();
}
