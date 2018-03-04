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
         const Color& emissive,
         const Color& specular,
         int specularPower);

      Material GetMaterial(int index);
      int GetMaterialCount() const;

   private:
      //TODO: Remove this, by using shared_ptr.
      MaterialLibrary_impl& GetImpl();

      std::unique_ptr<MaterialLibrary_impl> m_impl;

      friend class Engine_impl;
   };
}
