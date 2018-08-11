#pragma once

#include "Include/Material.h"
#include "Include/MaterialLibrary.h"

#include <deque>

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

      Material CreateMaterial(
         const Color& color);

      Material CreateMaterial(
         const Color& diffuse,
         const Color& emissive,
         const Color& specular,
         int specularPower);

      Material CreateUnlitMaterial(
         const Color& color);

      Material GetMaterial(unsigned index);
      int GetMaterialCount() const;

      //Internal
      const Material_impl& GetMaterialImpl(unsigned index) const;

   private:
      Material AddMaterial(
         const Color& diffuse,
         const Color& emissive,
         const Color& specular,
         int specularPower,
         bool isLit);

      MaterialLibrary& m_parent;

      unsigned m_nextMaterialID;
      std::deque<std::shared_ptr<Material_impl>> m_materials;
   };
}
