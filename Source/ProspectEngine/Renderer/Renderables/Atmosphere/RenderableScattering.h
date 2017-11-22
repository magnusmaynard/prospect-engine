#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Renderables/Atmosphere/RenderableSun.h"

namespace Prospect
{
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class RenderableScattering
   {
   public:
      RenderableScattering(const GlobalUniformBuffers& globalUniformBuffers);
      ~RenderableScattering();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:

      mutable bool m_isDirty;

      Shader& m_atmosphereShader;
      UniformBuffer<AtmosphereUniforms> m_atmosphereUniformBuffer;
   };
}
