#pragma once
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Scene/Terrain/Terrain_impl.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Pipeline/Shaders/TerrainShader.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;
   class Scene_impl;
   class IRenderable;

   class RenderableTerrain
   {
   public:
      RenderableTerrain(
         ShaderLibrary& shaderLibrary,
         const Terrain_impl& terrain);
      ~RenderableTerrain();

      void Render();

   private:
      void ConstructHeightMapTexture();

      const Terrain_impl& m_terrain;

      TerrainShader& m_shader;

      GLint m_maxHeightLocation;
      GLint m_minHeightLocation;
      GLint m_totalSizeLocation;

      GLuint m_VAO;
      GLuint m_texture;
      glm::mat4 m_transform;
   };
}
