#pragma once

#include "Include/Material.h"
#include "Include/MaterialLibrary.h"

#include <deque>
#include "Engine/EngineDefines.h"

namespace Prospect
{
   class MaterialLibrary;
   class Material;

   class MaterialLibrary_impl
   {
   public:
      MaterialLibrary_impl(MaterialLibrary& parent);

      Material CreateMaterial(
         const Color& diffuse,
         const Color& ambient,
         const Color& specular,
         float specularPower);

      Material GetMaterialAtIndex(int index);
      int GetMaterialCount() const;

   private:
      MaterialLibrary& m_parent;

      unsigned long m_nextMaterialID = NULL_ID;
      std::deque<std::shared_ptr<Material_impl>> m_materials;
   };
}
