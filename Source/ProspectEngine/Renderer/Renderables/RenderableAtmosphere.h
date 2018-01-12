#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/GBuffer.h"

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
         const GBuffer& gBuffer,
         const Atmosphere_impl& atmosphere);
      ~RenderableAtmosphere();

      void Render() override;
      void MakeDirty() override;

   private:
      void UpdateUniformsIfDirty();

      AtmosphereShader& m_shader;
      const GBuffer& m_gBuffer;
      const Atmosphere_impl& m_atmosphere;

      mutable bool m_isDirty;
   };
}
