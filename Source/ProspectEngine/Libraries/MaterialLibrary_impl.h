#pragma once

#include "Include/Material.h"
#include "Include/MaterialLibrary.h"

#include <deque>
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

      unsigned long m_nextMaterialID = NULL_ID;
      std::deque<Material> m_materials;
   };
}
