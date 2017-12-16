#pragma once
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class TextShader : public Shader
   {
   public:
      TextShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::TEXT_VERTEX_SHADER,
            Resources::TEXT_FRAGMENT_SHADER)
      {
         globalUniforms.Camera.Bind(GetProgram());
      }
   };
}
