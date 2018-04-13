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
            Resources::Shaders::TEXT_VERTEX,
            Resources::Shaders::TEXT_FRAGMENT)
      {
         globalUniforms.Camera.Bind(GetProgram());
      }
   };
}
