#pragma once

namespace Prospect
{
   class Material_impl;
   struct Color;

   class Material
   {
   public:
      ~Material();
      Material(const Material& other) = delete;
      Material& operator=(const Material& other) = delete;
      Material(Material&& other);
      Material& operator=(Material&& other);

      const Color& GetDiffuse() const;

      unsigned long GetID() const;

   private:
      Material(unsigned long id);
      Material(unsigned long id, const Color& diffuse);

      std::unique_ptr<Material_impl> m_impl;

      friend class MaterialLibrary_impl;
   };
}
