#include "ProspectEngine_pch.h"

#include "MaterialLibrary_impl.h"

#include "Include/Color.h"
#include "Include/Material.h"
#include "Scene/Material_impl.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

MaterialLibrary_impl::MaterialLibrary_impl(MaterialLibrary& parent)
   :
   m_parent(parent),
   m_nextMaterialID(0)
{
   //Add first material, this is not rendered in the lighting stage.
   //This material is used by default, as the GBuffer is cleared to use an ID of 0.
   AddMaterial(Color::Black(), Color::Black(), Color::Black(), 0, false);
}

Material MaterialLibrary_impl::CreateMaterial()
{
   return AddMaterial(
      Defaults::MATERIAL_DIFFUSE,
      Defaults::MATERIAL_EMISSIVE,
      Defaults::MATERIAL_SPECULAR,
      Defaults::MATERIAL_SPECULAR_POWER,
      true);
}

Material MaterialLibrary_impl::CreateMaterial(const Color& color)
{
   return AddMaterial(
      color,
      Defaults::MATERIAL_EMISSIVE,
      Defaults::MATERIAL_SPECULAR,
      Defaults::MATERIAL_SPECULAR_POWER,
      true);
}

Material MaterialLibrary_impl::CreateMaterial(
   const Color& diffuse,
   const Color& emissive,
   const Color& specular,
   const int specularPower)
{
   return AddMaterial(
      diffuse,
      emissive,
      specular,
      specularPower,
      true);
}

Material MaterialLibrary_impl::CreateUnlitMaterial(const Color& color)
{
   return AddMaterial(
      color,
      Defaults::MATERIAL_EMISSIVE,
      Defaults::MATERIAL_SPECULAR,
      Defaults::MATERIAL_SPECULAR_POWER,
      false);
}

Material MaterialLibrary_impl::GetMaterial(const unsigned index)
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return m_materials[index];
}

const Material_impl& MaterialLibrary_impl::GetMaterialImpl(const unsigned index) const
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return *m_materials[index].get();
}

Material MaterialLibrary_impl::AddMaterial(
   const Color& diffuse,
   const Color& emissive,
   const Color& specular,
   int specularPower,
   bool isLit)
{
   m_materials.emplace_back(std::make_shared<Material_impl>(
      m_nextMaterialID,
      diffuse,
      emissive,
      specular,
      specularPower,
      isLit));

   m_nextMaterialID++;

   return m_materials.back();
}

int MaterialLibrary_impl::GetMaterialCount() const
{
   return static_cast<int>(m_materials.size());
}
