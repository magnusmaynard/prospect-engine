#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class LightingShader : public Shader
   {
   public:
      LightingShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::QUAD_VERTEX_SHADER,
            Resources::LIGHTING_FRAGMENT_SHADER)
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.Lights.Bind(GetProgram());
         globalUniforms.MaterialLibrary.Bind(GetProgram());
      }
   };
}
