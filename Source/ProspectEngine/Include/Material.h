#pragma once

namespace Prospect
{
   class Material_impl;
   struct Color;

   class Material
   {
   public:
      ~Material();
      Material(std::shared_ptr<Material_impl>& impl);

      const Color& GetDiffuse() const;
      unsigned GetID() const;

   private:
      std::shared_ptr<Material_impl> m_impl;

      friend class Entity_impl;
      friend class MaterialLibrary_impl;
   };
}
