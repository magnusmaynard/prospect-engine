#pragma once

#include "Include/Material.h"
#include "Include/MaterialLibrary.h"

#include <vector>
#include "EngineDefines.h"

namespace Prospect
{
   class MaterialLibrary;
   class Material;

   class MaterialLibrary_impl
   {
   public:
      MaterialLibrary_impl(MaterialLibrary& parent);

      Material& CreateMaterial(const Color& color);

      Material& GetMaterialAtIndex(int index);

   private:
      MaterialLibrary& m_parent;

      unsigned long m_nextMaterialID = DEFAULT_MATERIAL_ID;
      std::vector<Material> m_materials;
   };
}
