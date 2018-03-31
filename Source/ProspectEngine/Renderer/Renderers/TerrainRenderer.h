#pragma once
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Scene/Terrain/Terrain_impl.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Pipeline/Shaders/TerrainShader.h"
#include "Renderer/Renderers/RenderDataLibrary.h"
#include "Renderer/Renderers/RenderData.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;
   class Scene_impl;

   struct TerrainRenderData : RenderData
   {
      GLuint VAO;
      GLuint HeightMapTexture;
      GLuint GroundTexture;
      glm::mat4 Transform;
   };

   class TerrainRenderer
   {
   public:
      TerrainRenderer(ShaderLibrary& shaderLibrary);
      ~TerrainRenderer();

      static void Initialise(TerrainRenderData& renderData);
      static void Dispose(TerrainRenderData& renderData);

      void Render(const Terrain_impl& terrain);

   private:
      static void ConstructHeightMapTexture(const Terrain_impl& terrain, TerrainRenderData& renderable);
      static void ConstructGroundTexture(const Terrain_impl& terrain, TerrainRenderData& renderable);

      TerrainShader& m_shader;
      RenderDataLibrary<TerrainRenderData> m_renderDataLibrary;
   };
}
