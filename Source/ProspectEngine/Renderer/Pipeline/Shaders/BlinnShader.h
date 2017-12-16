#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class BlinnShader : public Shader
   {
      public:
      BlinnShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::BLINNPHONG_VERTEX_SHADER,
            Resources::BLINNPHONG_FRAGMENT_SHADER),
         m_entityUniforms("EntityUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.DirectionalLight.Bind(GetProgram());
         globalUniforms.Materials.Bind(GetProgram());
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
