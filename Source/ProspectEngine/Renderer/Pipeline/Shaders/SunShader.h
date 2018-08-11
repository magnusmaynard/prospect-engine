#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class SunShader : public Shader
   {
   public:
      SunShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::Shaders::SUN_VERTEX,
            Resources::Shaders::SUN_FRAGMENT),
         m_sunUniforms("SunUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.MaterialLibrary.Bind(GetProgram());
         m_sunUniforms.Bind(GetProgram());
      }

      void Update(const SunUniforms& block)
      {
         m_sunUniforms.Update(block);
      }

   private:
      UniformBuffer<SunUniforms> m_sunUniforms;
   };
}
