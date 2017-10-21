#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Include/Bitmap.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Scene/Terrain/Terrain.h"

namespace Prospect
{
   struct GlobalUniformBuffers;
   class Scene_impl;

   class RenderableTerrain
   {
   public:
      RenderableTerrain(
         const Terrain& terrain,
         const GlobalUniformBuffers& globalUniformBuffers);
      ~RenderableTerrain();

      void Render();

   private:
      void ConstructHeightMapTexture();

      const Terrain& m_terrain;

      Shader& m_shader;

      GLint m_maxHeightLocation;
      GLint m_minHeightLocation;
      GLint m_totalSizeLocation;

      GLuint m_VAO;
      GLuint m_texture;
      glm::mat4 m_transform;

      UniformBuffer<NodeUniforms, 1> m_nodeUniformBuffer;
   };
}
