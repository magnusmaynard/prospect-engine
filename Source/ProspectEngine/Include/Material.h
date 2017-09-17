#pragma once

#include "Color.h"

namespace Prospect
{
   class Material
   {
   public:
      //TODO: Make internal
      Material(unsigned long id);
      Material(unsigned long id, const Color& diffuse);
      ~Material(){}

      const Color& GetDiffuse() const;

      unsigned long GetID() const;

   private:
      unsigned long m_id;

      Color m_diffuse;
   };
}
