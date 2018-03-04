#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class TerrainShader : public Shader
   {
   public:
      TerrainShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::TERRAIN_VERTEX_SHADER,
            Resources::TERRAIN_TESSCONTROL_SHADER,
            Resources::TERRAIN_TESSEVALUATION_SHADER,
            Resources::TERRAIN_FRAGMENT_SHADER),
         m_nodeUniforms("NodeUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.DirectionalLights.Bind(GetProgram());
         m_nodeUniforms.Bind(GetProgram());
      }

      void Update(const NodeUniforms& block)
      {
         m_nodeUniforms.Update(block);
      }

   private:
      UniformBuffer<NodeUniforms> m_nodeUniforms;
   };
}
