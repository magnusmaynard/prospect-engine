#include "ProspectEngine_pch.h"

#include "Renderer/Renderers/TerrainRenderer.h"
#include <noise/noise.h>

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Renderables/Renderable.h"

using namespace Prospect;
using namespace noise;
using namespace glm;

TerrainRenderer::TerrainRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetTerrainShader())
{
}

TerrainRenderer::~TerrainRenderer()
{
   //Dispose.
   for(auto& renderable : m_terrainRenderables)
   {
      glDeleteVertexArrays(1, &renderable.second.VAO);
   }
}

void TerrainRenderer::Render(const Terrain_impl& terrain)
{
   TerrainRenderable& renderable = GetTerrainRenderable(terrain);

   //Update textures if dirty.
   if(terrain.IsDirty())
   {
      ConstructHeightMapTexture(terrain, renderable);
      terrain.Clean();
   }

   //Bind.
   m_shader.Bind();
   glBindVertexArray(renderable.VAO);

   m_shader.Update(TerrainUniforms(terrain));

   //Textures.
   glBindTextureUnit(0, renderable.HeightMapTexture);

   //Draw.
   auto& endNodes = terrain.GetEndNodes();
   for (auto& node : endNodes)
   {
      //Draw this node.
      m_shader.Update(NodeUniforms(
         node->Origin(),
         node->Edges(),
         node->Size(),
         node->Level()));

      glPatchParameteri(GL_PATCH_VERTICES, 4);
      glDrawArrays(GL_PATCHES, 0, 4);
   }
}

TerrainRenderable& TerrainRenderer::GetTerrainRenderable(
   const Terrain_impl& terrain)
{
   auto itr = m_terrainRenderables.find(terrain.GetId());
   if (itr == m_terrainRenderables.end())
   {
      TerrainRenderable renderable;
      glCreateVertexArrays(1, &renderable.VAO);

      return m_terrainRenderables.emplace(terrain.GetId(), renderable).first->second;
   }

   return itr->second;
}

void TerrainRenderer::ConstructHeightMapTexture(
   const Terrain_impl& terrain,
   TerrainRenderable& renderable)
{
   auto& terrainMap = terrain.GetTerrainMap();

   glCreateTextures(GL_TEXTURE_2D, 1, &renderable.HeightMapTexture);
   glTextureStorage2D(renderable.HeightMapTexture, 4, GL_R32F, terrainMap.Width, terrainMap.Height);
   glTextureSubImage2D(
      renderable.HeightMapTexture,
      0,
      0, 0,
      terrainMap.Width, terrainMap.Height,
      GL_RED,
      GL_FLOAT,
      &terrainMap.Data[0]);

   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_MAX_LEVEL, 4);
   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glGenerateTextureMipmap(renderable.HeightMapTexture);

   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(renderable.HeightMapTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
