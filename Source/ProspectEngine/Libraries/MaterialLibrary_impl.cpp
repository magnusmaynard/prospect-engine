#include "ProspectEngine_pch.h"

#include "MaterialLibrary_impl.h"

#include "Include/Color.h"
#include "Include/Material.h"
#include "Scene/Material_impl.h"

using namespace Prospect;

MaterialLibrary_impl::MaterialLibrary_impl(MaterialLibrary& parent)
   :
   m_parent(parent)
{
}

Material MaterialLibrary_impl::CreateMaterial(const Color& color)
{
   m_nextMaterialID++;

   m_materials.emplace_back(std::make_shared<Material_impl>(m_nextMaterialID, color));

   return m_materials.back();
}

Material MaterialLibrary_impl::GetMaterialAtIndex(int index)
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return m_materials[index];
}

int MaterialLibrary_impl::GetMaterialCount() const
{
   return m_materials.size();
}
