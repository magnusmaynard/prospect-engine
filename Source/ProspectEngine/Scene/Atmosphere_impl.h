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

      void SetSunDirection(const glm::vec3& value); //TODO: use zenith/time of day
      glm::vec3 GetSunDirection() const;

   private:
      Atmosphere& m_parent;
      IRenderable* m_renderable;
      mutable bool m_isDirty;

      float m_altitude;
      const Light* m_lightSource;
      glm::vec3 m_sunDirection;
   };
}