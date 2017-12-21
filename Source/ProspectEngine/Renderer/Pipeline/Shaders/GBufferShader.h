#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class GBufferShader : public Shader
   {
   public:
      GBufferShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::GBUFFER_VERTEX_SHADER,
            Resources::GBUFFER_FRAGMENT_SHADER)
      {
      }
   };
}
