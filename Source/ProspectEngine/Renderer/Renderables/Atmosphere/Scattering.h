#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Pipeline/Shaders/ScatteringShader.h"

namespace Prospect
{
   class ShaderLibrary;
   class DepthTexture;
   class Atmosphere_impl;

   class Scattering
   {
   public:
      Scattering(
         ShaderLibrary& shaderLibrary,
         const DepthTexture& depthTexture);
      ~Scattering();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:
      ScatteringShader& m_shader;
      const DepthTexture& m_depthTexture;
   };
}
