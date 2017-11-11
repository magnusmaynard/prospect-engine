#pragma once

#include <memory>
#include "Defaults.h"

namespace Prospect
{
   struct Color;
   class Material;
   class MaterialLibrary_impl;

   class MaterialLibrary
   {
   public:
      MaterialLibrary();
      ~MaterialLibrary();

      Material CreateMaterial(
         const Color& diffuse = DEFAULT_MATERIAL_DIFFUSE,
         const Color& ambient = DEFAULT_MATERIAL_AMBIENT,
         const Color& specular = DEFAULT_MATERIAL_SPECULAR,
         float specularPower = DEFAULT_MATERIAL_SPECULAR_POWER);

      Material GetMaterialAtIndex(int index);
      int GetMaterialCount() const;

   private:
      std::unique_ptr<MaterialLibrary_impl> m_impl;
   };
}
