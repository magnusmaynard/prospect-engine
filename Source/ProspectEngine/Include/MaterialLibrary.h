#pragma once

#include "Defines.h"
#include <memory>

namespace Prospect
{
   struct Color;
   class Material;
   class MaterialLibrary_impl;

   class MaterialLibrary
   {
   public:
      EXPORT_DLL MaterialLibrary();
      EXPORT_DLL ~MaterialLibrary();

      EXPORT_DLL Material& CreateMaterial(const Color& color);
      EXPORT_DLL Material& GetMaterialAtIndex(int index);

   private:
      std::unique_ptr<MaterialLibrary_impl> m_impl;
   };
}
