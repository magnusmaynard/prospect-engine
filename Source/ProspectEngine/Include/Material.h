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
      unsigned long GetID() const;

   private:
      Material(unsigned long id);
      Material(unsigned long id, const Color& diffuse);

      std::shared_ptr<Material_impl> m_impl;

      friend class Entity_impl;
      friend class MaterialLibrary_impl;
   };
}
