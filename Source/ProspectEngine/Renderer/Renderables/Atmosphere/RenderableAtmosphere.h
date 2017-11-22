#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Renderables/Atmosphere/RenderableSun.h"
#include "Renderer/Renderables/Atmosphere/RenderableScattering.h"

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
      RenderableScattering m_scattering;
      RenderableSun m_sun;
   };
}
