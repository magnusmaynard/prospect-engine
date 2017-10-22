#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   struct GlobalUniformBuffers;

   class RenderableAtmosphere : public IRenderable
   {
   public:
      RenderableAtmosphere(const GlobalUniformBuffers& globalUniformBuffers);
      ~RenderableAtmosphere();

      void Render() override;

   private:
      Shader& m_shader;

      glm::vec3 m_eyePosition;

      //UniformBuffer<AtmosphereUniforms> m_atmosphereUniformBuffer;
   };
}
