#include "ProspectEngine_pch.h"

#include "MaterialLibrary_impl.h"

#include "Include/Color.h"
#include "Include/Material.h"
#include "Scene/Material_impl.h"

using namespace Prospect;

MaterialLibrary_impl::MaterialLibrary_impl(MaterialLibrary& parent)
   :
   m_parent(parent),
   m_nextMaterialID(0)
{
}

Material MaterialLibrary_impl::CreateMaterial()
{
   return CreateMaterial(
      DEFAULT_MATERIAL_DIFFUSE,
      DEFAULT_MATERIAL_AMBIENT,
      DEFAULT_MATERIAL_SPECULAR,
      DEFAULT_MATERIAL_SPECULAR_POWER);
}

Material MaterialLibrary_impl::CreateMaterial(const Color& diffuse)
{
   return CreateMaterial(
      diffuse,
      DEFAULT_MATERIAL_AMBIENT,
      DEFAULT_MATERIAL_SPECULAR,
      DEFAULT_MATERIAL_SPECULAR_POWER);
}

Material MaterialLibrary_impl::CreateMaterial(
   const Color& diffuse,
   const Color& ambient,
   const Color& specular,
   const int specularPower)
{
   m_materials.emplace_back(std::make_shared<Material_impl>(
      m_nextMaterialID,
      diffuse,
      ambient,
      specular,
      specularPower));

   m_nextMaterialID++;

   return m_materials.back();
}

Material MaterialLibrary_impl::GetMaterial(const int index)
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return m_materials[index];
}

const Material_impl& MaterialLibrary_impl::GetMaterialImpl(const int index) const
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return *m_materials[index].get();
}

int MaterialLibrary_impl::GetMaterialCount() const
{
   return m_materials.size();
}
