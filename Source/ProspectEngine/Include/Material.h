#pragma once
#include "Defines.h"
#include "Color.h"

namespace Prospect
{
   class EXPORT_DLL Material
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
