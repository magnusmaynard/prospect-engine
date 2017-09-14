#include "MaterialLibrary_impl.h"

#include <vector>
#include "Include/Color.h"

using namespace Prospect;

MaterialLibrary_impl::MaterialLibrary_impl(MaterialLibrary& parent)
   :
   m_parent(parent)
{
   //Reserve so adding new materials does not invalidate references to them.
   m_materials.reserve(MAX_MESHES);
}

Material& MaterialLibrary_impl::CreateMaterial(const Color& color)
{
   m_nextMaterialID++;

   m_materials.emplace_back(m_nextMaterialID, color);

   return m_materials.back();
}

Material& MaterialLibrary_impl::GetMaterialAtIndex(int index)
{
   if (index < 0 || index >= static_cast<int>(m_materials.size()))
   {
      throw std::exception("No Mesh at index.");
   }

   return m_materials[index];
}
