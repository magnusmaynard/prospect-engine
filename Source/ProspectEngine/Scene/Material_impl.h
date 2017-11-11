#pragma once

#include "Include/Color.h"
#include "Include/Material.h"

namespace Prospect
{
   class Material_impl
   {
   public:
      //Public
      const Color& GetDiffuse() const;
      unsigned long GetID() const;

      //Internal
      Material_impl(unsigned long id);
      Material_impl(unsigned long id, const Color& diffuse);

   private:
      unsigned long m_id;

      Color m_diffuse;
   };
}
