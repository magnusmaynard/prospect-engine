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

      Material CreateMaterial();

      Material CreateMaterial(
         const Color& diffuse);

      Material CreateMaterial(
         const Color& diffuse,
         const Color& ambient,
         const Color& specular,
         float specularPower);

      Material GetMaterialAtIndex(int index);
      int GetMaterialCount() const;

   private:
      std::unique_ptr<MaterialLibrary_impl> m_impl;
   };
}
