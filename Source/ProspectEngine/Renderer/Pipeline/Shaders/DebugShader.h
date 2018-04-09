#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class DebugShader : public Shader
   {
   public:
      DebugShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::DEBUG_VERTEX_SHADER,
            Resources::DEBUG_FRAGMENT_SHADER)
      {
         globalUniforms.Camera.Bind(GetProgram());
      }
   };
}
