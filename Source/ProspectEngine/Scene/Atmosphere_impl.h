#pragma once
#include "Include/Atmosphere.h"

namespace Prospect
{
   class Atmosphere_impl
   {
      class IRenderable;

   public:
      Atmosphere_impl(Atmosphere& parent);
      ~Atmosphere_impl();

      void SetAltitude(float height);
      float GetAltitude() const;

      void SetLightSource(const Light& lightSource);
      const Light* GetLightSource() const;

      //Rayleigh
      //Mie

      //MinRadius
      //MaxRadius
      //HeightOfAverageDensity

   private:
      Atmosphere& m_parent;
      IRenderable* m_renderable;
      mutable bool m_isDirty;

      float m_altitude;
      const Light* m_lightSource;
   };
}