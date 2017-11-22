#pragma once

#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class Clouds
   {
   public:
      Clouds(const GlobalUniformBuffers& globalUniformBuffers);
      ~Clouds();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:

      Shader& m_shader;
      UniformBuffer<ScatteringUniforms> m_uniformBuffer;
   };
}
