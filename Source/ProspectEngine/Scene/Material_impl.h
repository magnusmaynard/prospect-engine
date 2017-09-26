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
      Material_impl(Material& parent, unsigned long id);
      Material_impl(Material& parent, unsigned long id, const Color& diffuse);

   private:
      Material& m_parent;
      unsigned long m_id;

      Color m_diffuse;
   };
}
