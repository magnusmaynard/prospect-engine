#pragma once

namespace Prospect
{
   class Light;
   class Atmosphere_impl;

   class Atmosphere
   {
   public:
      Atmosphere();
      Atmosphere(std::shared_ptr<Atmosphere_impl>& impl);
      ~Atmosphere();

      void SetAltitude(float height);
      float GetAltitude() const;

      void SetLightSource(const Light& lightSource);
      const Light* GetLightSource() const;

   private:
      std::shared_ptr<Atmosphere_impl> m_impl;

      friend class Scene_impl;
   };
}