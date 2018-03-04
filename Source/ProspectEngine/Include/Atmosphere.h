#pragma once

namespace Prospect
{
   class DirectionalLight;
   class Light;
   class Atmosphere_impl;

   class Atmosphere
   {
   public:
      Atmosphere();
      Atmosphere(std::shared_ptr<Atmosphere_impl>& impl);
      ~Atmosphere();

      void SetLight(DirectionalLight& light);
      DirectionalLight GetLight();

      void SetSunDirection(const glm::vec3& value);
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
      std::shared_ptr<Atmosphere_impl> m_impl;

      friend class Scene_impl;
   };
}