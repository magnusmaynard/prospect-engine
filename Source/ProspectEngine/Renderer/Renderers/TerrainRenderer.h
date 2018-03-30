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

   struct TerrainRenderable
   {
      GLuint VAO;
      GLuint HeightMapTexture;
      glm::mat4 Transform;
   };

   class TerrainRenderer
   {
   public:
      TerrainRenderer(ShaderLibrary& shaderLibrary);
      ~TerrainRenderer();

      void Render(const Terrain_impl& terrain);

   private:
      TerrainRenderable& GetRenderable(const Terrain_impl& terrain);
      void ConstructHeightMapTexture(const Terrain_impl& terrain, TerrainRenderable& renderable);

      TerrainShader& m_shader;

      std::map<unsigned, TerrainRenderable> m_terrainRenderables;
   };
}
