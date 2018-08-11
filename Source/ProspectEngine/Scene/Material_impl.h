#pragma once

#include "Include/Color.h"
#include "Include/Material.h"

namespace Prospect
{
   class Material_impl
   {
   public:
      //Public
      unsigned GetID() const;

      void SetDiffuse(const Color& value);
      const Color& GetDiffuse() const;

      void SetEmissive(const Color& value);
      const Color& GetEmissive() const;

      void SetSpecular(const Color& value);
      const Color& GetSpecular() const;

      void SetSpecularPower(int value);
      int GetSpecularPower() const;

      void SetIsLit(bool value);
      bool GetIsLit() const;

      //Internal
      Material_impl(
         unsigned id,
         const Color& diffuse,
         const Color& ambient,
         const Color& specular,
         int specularPower,
         bool isLit);

   private:
      unsigned m_id;

      Color m_diffuse;
      Color m_emissive;
      Color m_specular;
      int m_specularPower;

      bool m_isLit;
   };
}
