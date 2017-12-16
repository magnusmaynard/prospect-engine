#include "ProspectEngine_pch.h"

#include "Renderer/Renderables/RenderableTerrain.h"
#include <noise/noise.h>

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/Shaders/Shader.h"

using namespace Prospect;
using namespace noise;
using namespace glm;

RenderableTerrain::RenderableTerrain(
   ShaderLibrary& shaderLibrary,
   const Terrain_impl& terrain)
   :
   m_terrain(terrain),
   m_shader(shaderLibrary.GetTerrainShader())
{
   m_minHeightLocation = m_shader.GetUniformLocation("minHeight");
   m_maxHeightLocation = m_shader.GetUniformLocation("maxHeight");
   m_totalSizeLocation = m_shader.GetUniformLocation("totalSize");

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   ConstructHeightMapTexture();
}

RenderableTerrain::~RenderableTerrain()
{
   //Dispose.
   glDeleteVertexArrays(1, &m_VAO);
}

void RenderableTerrain::Render()
{
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

   //Bind.
   m_shader.Bind();

   //Uniforms.
   glUniform1f(m_minHeightLocation, m_terrain.GetMinHeight());
   glUniform1f(m_maxHeightLocation, m_terrain.GetMaxHeight());
   glUniform1f(m_totalSizeLocation, m_terrain.GetSize());

   //Textures.
   glBindTextureUnit(0, m_texture);

   //Draw.
   auto& endNodes = m_terrain.GetEndNodes();
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

void RenderableTerrain::ConstructHeightMapTexture()
{
   auto& terrainMap = m_terrain.GetTerrainMap();

   glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
   glTextureStorage2D(m_texture, 4, GL_R32F, terrainMap.Width, terrainMap.Height);
   glTextureSubImage2D(
      m_texture,
      0,
      0, 0,
      terrainMap.Width, terrainMap.Height,
      GL_RED,
      GL_FLOAT,
      &terrainMap.Data[0]);

   glTextureParameteri(m_texture, GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(m_texture, GL_TEXTURE_MAX_LEVEL, 4);
   glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glGenerateTextureMipmap(m_texture);

   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
