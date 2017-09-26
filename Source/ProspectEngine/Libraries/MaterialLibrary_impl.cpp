#include "MaterialLibrary_impl.h"

#include <vector>
#include "Include/Color.h"
#include "Include/Material.h"

using namespace Prospect;

MaterialLibrary_impl::MaterialLibrary_impl(MaterialLibrary& parent)
   :
   m_parent(parent)
{
}

Material& MaterialLibrary_impl::CreateMaterial(const Color& color)
{
   m_nextMaterialID++;

   m_materials.emplace_back(Material(m_nextMaterialID, color));

   return m_materials.back();
}

Material& MaterialLibrary_impl::GetMaterialAtIndex(int index)
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Material at index.");
   }

   return m_materials[index];
}
