#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

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

   private:
      UniformBuffer<AtmosphereUniforms> m_atmosphereUniformBuffer;
      const Atmosphere_impl& m_atmosphere;

      Shader& m_shader;

      glm::vec3 m_eyePosition;

   };
}
