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
   m_shader(shaderLibrary.GetTerrainShader()),
   m_grassRenderer(shaderLibrary)
{
   m_renderDataLibrary.SetInitialise(Initialise);
   m_renderDataLibrary.SetDispose(Dispose);
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Initialise(TerrainRenderData& renderData)
{
   glCreateVertexArrays(1, &renderData.VAO);
}

void TerrainRenderer::Dispose(TerrainRenderData& renderData)
{
   glDeleteVertexArrays(1, &renderData.VAO);
}

void TerrainRenderer::Render(const Terrain_impl& terrain)
{
   TerrainRenderData& renderData = m_renderDataLibrary.GetRenderData(terrain.GetId());

   //Update state.
   glDepthMask(GL_TRUE);
   glEnable(GL_DEPTH_TEST);
   glBlendFunc(GL_ONE, GL_ZERO);
   glEnable(GL_CULL_FACE);

   //Update textures if dirty.
   if(terrain.IsDirty())
   {
      ConstructHeightMapTexture(terrain, renderData);
      ConstructGroundTexture(terrain, renderData);

      terrain.Clean();
   }

   //Bind.
   m_shader.Bind();
   glBindVertexArray(renderData.VAO);

   m_shader.Update(TerrainUniforms(terrain));

   //Textures.
   glBindTextureUnit(0, renderData.HeightMapTexture);
   glBindTextureUnit(1, renderData.GroundTexture);

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

   //Draw grass.
   m_grassRenderer.Render(terrain, renderData);
}

void TerrainRenderer::ConstructHeightMapTexture(
   const Terrain_impl& terrain,
   TerrainRenderData& renderable)
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

void TerrainRenderer::ConstructGroundTexture(const Terrain_impl& terrain, TerrainRenderData& renderable)
{
   if(!terrain.GetGroundTexture())
   {
      return;
   }

   auto& groundTexture = *terrain.GetGroundTexture();

   if(groundTexture.Channels != 3)
   {
      std::cout << "Error: Invalid texture" << std::endl;
      return;
   }

   const int mipmapLevels = 8;

   glCreateTextures(GL_TEXTURE_2D, 1, &renderable.GroundTexture);
   glTextureStorage2D(renderable.GroundTexture, mipmapLevels, GL_RGB32F, groundTexture.Width, groundTexture.Height);
   glTextureSubImage2D(
      renderable.GroundTexture,
      0,
      0, 0,
      groundTexture.Width, groundTexture.Height,
      GL_RGB,
      GL_FLOAT,
      &groundTexture.Data[0]);

   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_MAX_LEVEL, mipmapLevels);
   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   GLfloat maxAnisotropy;
   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
   glTextureParameterf(renderable.GroundTexture, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

   glGenerateTextureMipmap(renderable.GroundTexture);

   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTextureParameteri(renderable.GroundTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
