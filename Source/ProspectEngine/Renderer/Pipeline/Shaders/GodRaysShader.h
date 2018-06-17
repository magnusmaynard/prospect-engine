#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class GodRaysShader : public Shader
   {
   public:
      GodRaysShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::Shaders::QUAD_VERTEX,
            Resources::Shaders::GODRAYS_FRAGMENT),
         m_godRaysUniforms("GodRaysUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         m_godRaysUniforms.Bind(GetProgram());
      }

      void Update(const GodRaysUniforms& block)
      {
         m_godRaysUniforms.Update(block);
      }

   private:
      UniformBuffer<GodRaysUniforms> m_godRaysUniforms;
   };
}
