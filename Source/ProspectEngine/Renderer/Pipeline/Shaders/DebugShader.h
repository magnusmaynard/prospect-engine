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
            
            Resources::Shaders::DEBUG_VERTEX,
            Resources::Shaders::DEBUG_FRAGMENT)
      {
         globalUniforms.Camera.Bind(GetProgram());
      }
   };
}
