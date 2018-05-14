#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Pipeline/Shaders/TerrainShader.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class GrassShader : public Shader
   {
   public:
      GrassShader(
         const GlobalUniformBuffers& globalUniforms,
         TerrainShader& terrainShader)
         :
         Shader(
            Resources::Shaders::GRASS_VERTEX,
            Resources::Shaders::GRASS_GEOMETRY,
            Resources::Shaders::GRASS_FRAGMENT),
         m_grassUniforms("GrassUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         m_grassUniforms.Bind(GetProgram());
         terrainShader.GetTerrainUniforms().Bind(GetProgram());
      }

      void Update(const GrassUniforms& uniforms)
      {
         m_grassUniforms.Update(uniforms);
      }

   private:
      UniformBuffer<GrassUniforms> m_grassUniforms;
   };
}
