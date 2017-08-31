#pragma once
#include "Defines.h"
#include "Color.h"

namespace Prospect
{
   class EXPORT_DLL Material
   {
   public:
      Material();
      Material(const Color& color);
      Material(const Color& diffuse, const Color& ambient);

      const Color& GetDiffuse() const;
      const Color& GetAmbient() const;

   private:
      static const Color DEFAULT_COLOR;

      Color m_diffuse;
      Color m_ambient;
   };
}
