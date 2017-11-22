#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Renderables/Atmosphere/Sun.h"
#include "Renderer/Renderables/Atmosphere/Scattering.h"
#include "Renderer/Renderables/Atmosphere/Clouds.h"

namespace Prospect
{
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class RenderableAtmosphere : public IRenderable
   {
   public:
      RenderableAtmosphere(const GlobalUniformBuffers& globalUniformBuffers, const Atmosphere_impl& atmosphere);
      ~RenderableAtmosphere();

      void Render() override;
      void MakeDirty() override;

   private:
      void UpdateUniformsIfDirty();

      mutable bool m_isDirty;

      const Atmosphere_impl& m_atmosphere;

      Scattering m_scattering;
      Sun m_sun;
      Clouds m_clouds;
   };
}
