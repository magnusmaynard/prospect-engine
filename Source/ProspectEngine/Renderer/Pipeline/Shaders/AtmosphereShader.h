#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class AtmosphereShader : public Shader
   {
   public:
      AtmosphereShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::QUAD_VERTEX_SHADER,
            Resources::ATMOSPHERE_FRAGMENT_SHADER),
         m_atmosphereUniforms("AtmosphereUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         m_atmosphereUniforms.Bind(GetProgram());
      }

      void Update(const AtmosphereUniforms& block)
      {
         m_atmosphereUniforms.Update(block);
      }

   private:
      UniformBuffer<AtmosphereUniforms> m_atmosphereUniforms;
   };
}
