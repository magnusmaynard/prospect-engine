#pragma once

namespace Prospect
{
   class Light;
   class Atmosphere_impl;

   class Atmosphere
   {
   public:
      Atmosphere();
      ~Atmosphere();

      void SetAltitude(float height);
      float GetAltitude() const;

      void SetLightSource(const Light& lightSource);

   private:
      std::unique_ptr<Atmosphere_impl> m_impl;
   };
}