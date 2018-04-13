#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class BlinnPhongShader : public Shader
   {
      public:
      BlinnPhongShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::Shaders::BLINNPHONG_VERTEX,
            Resources::Shaders::BLINNPHONG_FRAGMENT),
         m_entityUniforms("EntityUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.MaterialLibrary.Bind(GetProgram());
         m_entityUniforms.Bind(GetProgram());
      }

      void Update(const EntityUniforms& block)
      {
         m_entityUniforms.Update(block);
      }
      
   private:
      UniformBuffer<EntityUniforms> m_entityUniforms;
   };
}
