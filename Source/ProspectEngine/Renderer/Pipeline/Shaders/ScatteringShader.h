#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class ScatteringShader : public Shader
   {
   public:
      ScatteringShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::SCATTERING_VERTEX_SHADER,
            Resources::SCATTERING_FRAGMENT_SHADER),
         m_scatteringUniforms("ScatteringUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         m_scatteringUniforms.Bind(GetProgram());
      }

      void Update(const ScatteringUniforms& block)
      {
         m_scatteringUniforms.Update(block);
      }

   private:
      UniformBuffer<ScatteringUniforms> m_scatteringUniforms;
   };
}
