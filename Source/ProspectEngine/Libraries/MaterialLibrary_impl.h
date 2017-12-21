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
      //Public
      MaterialLibrary_impl(MaterialLibrary& parent);

      Material CreateMaterial();

      Material CreateMaterial(const Color& color);

      Material CreateMaterial(
         const Color& diffuse,
         const Color& ambient,
         const Color& specular,
         int specularPower);

      Material GetMaterial(int index);
      int GetMaterialCount() const;

      //Internal
      const Material_impl& GetMaterialImpl(int index) const;

   private:
      MaterialLibrary& m_parent;

      unsigned long m_nextMaterialID;
      std::deque<std::shared_ptr<Material_impl>> m_materials;
   };
}
