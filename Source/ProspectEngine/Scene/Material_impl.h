#pragma once

#include "Include/Color.h"
#include "Include/Material.h"

namespace Prospect
{
   class Material_impl
   {
   public:
      //Public
      unsigned long GetID() const;

      void SetDiffuse(const Color& diffuse);
      const Color& GetDiffuse() const;

      void SetAmbient(const Color& ambient);
      const Color& GetAmbient() const;

      void SetSpecular(const Color& specular);
      const Color& GetSpecular() const;

      void SetSpecularPower(int specularPower);
      int GetSpecularPower() const;

      //Internal
      Material_impl(
         unsigned long id,
         const Color& diffuse,
         const Color& ambient,
         const Color& specular,
         int specularPower);

   private:
      unsigned long m_id;

      Color m_diffuse;
      Color m_ambient;
      Color m_specular;
      int m_specularPower;
   };
}
