#pragma once

#include <memory>

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

      Material CreateMaterial(const Color& color);
      Material GetMaterialAtIndex(int index);
      int GetMaterialCount() const;

   private:
      std::unique_ptr<MaterialLibrary_impl> m_impl;
   };
}
