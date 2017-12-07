#pragma once

#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   class DepthTexture;
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class Scattering
   {
   public:
      Scattering(
         const GlobalUniformBuffers& globalUniformBuffers,
         const DepthTexture& depthTexture);
      ~Scattering();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:
      Shader& m_shader;
      UniformBuffer<ScatteringUniforms> m_uniformBuffer;

      const DepthTexture& m_depthTexture;
   };
}
