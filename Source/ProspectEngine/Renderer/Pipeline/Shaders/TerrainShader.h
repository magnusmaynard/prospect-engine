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
            Resources::Shaders::TERRAIN_VERTEX,
            Resources::Shaders::TERRAIN_TESSCONTROL,
            Resources::Shaders::TERRAIN_TESSEVALUATION,
            Resources::Shaders::TERRAIN_FRAGMENT),
         m_terrainUniforms("TerrainUniforms"),
         m_nodeUniforms("NodeUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         m_terrainUniforms.Bind(GetProgram());
         m_nodeUniforms.Bind(GetProgram());
      }

      void Update(const TerrainUniforms& block)
      {
         m_terrainUniforms.Update(block);
      }

      void Update(const NodeUniforms& block)
      {
         m_nodeUniforms.Update(block);
      }

      //TODO: Come up with a better solution to shader uniforms between shaders, e.g. UniformBufferLibrary.
      UniformBuffer<TerrainUniforms>& GetTerrainUniforms()
      {
         return m_terrainUniforms;
      }

   private:
      UniformBuffer<TerrainUniforms> m_terrainUniforms;
      UniformBuffer<NodeUniforms> m_nodeUniforms;
   };
}
