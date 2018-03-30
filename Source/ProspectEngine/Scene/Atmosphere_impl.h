#pragma once
#include "Include/Atmosphere.h"
#include "Include/Lights/DirectionalLight.h"
#include "Renderer/Renderables/Renderable.h"

namespace Prospect
{
   class IRenderable;

   class Atmosphere_impl : public Renderable
   {
   public:
      //Public
      Atmosphere_impl();
      ~Atmosphere_impl();

      void SetLight(DirectionalLight& light);
      DirectionalLight GetLight();

      //TODO: Get/Set Rayleigh constant
      //TODO: Get/Set Mie constant

      void SetSunDirection(const glm::vec3& value); //TODO: use zenith/time of day
      glm::vec3 GetSunDirection() const;

      void SetInnerRadius(const float value);
      float GetInnerRadius() const;

      void SetOutterRadius(const float value);
      float GetOutterRadius() const;

      void SetAltitude(float height);
      float GetAltitude() const;

      //Height of average density of atmosphere.
      void SetDensityScale(const float value);
      float GetDensityScale() const;

   private:
      void UpdateLight();

      DirectionalLight m_light;

      float m_altitude;
      glm::vec3 m_sunDirection;
      float m_innerRadius;
      float m_outterRadius;
      float m_densityScale;
   };
}
