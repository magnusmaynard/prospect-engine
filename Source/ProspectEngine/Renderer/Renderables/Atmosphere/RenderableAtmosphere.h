#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Renderables/Atmosphere/Sun.h"
#include "Renderer/Renderables/Atmosphere/Scattering.h"

namespace Prospect
{
   class DepthTexture;
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class RenderableAtmosphere : public IRenderable
   {
   public:
      RenderableAtmosphere(
         ShaderLibrary& shaderLibrary,
         const DepthTexture& depthTexture,
         const Atmosphere_impl& atmosphere);
      ~RenderableAtmosphere();

      void Render() override;
      void MakeDirty() override;

   private:
      void UpdateUniformsIfDirty();

      const Atmosphere_impl& m_atmosphere;

      Scattering m_scattering;
      Sun m_sun;
      //Clouds m_clouds;

      mutable bool m_isDirty;
   };
}
