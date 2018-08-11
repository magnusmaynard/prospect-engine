#include "ProspectEngine_pch.h"

#include "GrassRenderer.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Renderers/TerrainRenderer.h"
#include "Include/Utilities/IO.h"
#include "Renderer/Debugger/Debug.h"

using namespace Prospect;

GrassRenderer::GrassRenderer(ShaderLibrary& shaderLibrary, MaterialLibrary_impl& materialLibrary)
   :
   m_shader(shaderLibrary.GetGrassShader()),
   m_material(materialLibrary.CreateMaterial(Color(0.28f, 0.35f, 0.07f)))
{
   m_renderDataLibrary.SetInitialise(Initialise);
   m_renderDataLibrary.SetDispose(Dispose);
}

GrassRenderer::~GrassRenderer()
{
}

void GrassRenderer::Render(const Terrain_impl& terrain, const TerrainRenderData& terrainRenderData)
{
   GrassRenderData& renderData = m_renderDataLibrary.GetRenderData(terrain.GetId());

   m_shader.Bind();
   glBindTextureUnit(0, terrainRenderData.HeightMapTexture);
   glBindTextureUnit(1, 8);// renderData.NoiseTexture);
   glBindVertexArray(renderData.VAO);

   Debug::CheckErrors();
   glDisable(GL_CULL_FACE);

   const glm::vec3 pos = terrain.GetLodPosition();

   //for (int y = -1; y < 2; ++y)
   //{
   //   for (int x = -1; x < 2; ++x)
   //   {

         //const glm::vec2 patchOffset(x * renderData.PatchSize, y * renderData.PatchSize);
   
         const glm::vec2 patchOffset(0, 0);
         m_shader.Update({ patchOffset, m_material.GetID() });
         glDrawArrays(GL_POINTS, 0, renderData.Points.size());
      //}
   //}
}

void GrassRenderer::Initialise(GrassRenderData& renderData)
{
   Debug::CheckErrors();
   renderData.PatchSize = 120.f;
   renderData.PatchGrassRows = 200;

   const int halfRows = static_cast<int>(renderData.PatchGrassRows * 0.5);
   const float grassSpacing = renderData.PatchSize / renderData.PatchGrassRows;

   //Create grid of points.
   renderData.Points.reserve(static_cast<int>(renderData.PatchGrassRows * renderData.PatchGrassRows));

   for (int z = -halfRows; z < halfRows; ++z)
   {
      for (int x = -halfRows; x < halfRows; ++x)
      {
         renderData.Points.push_back(glm::vec3(x * grassSpacing, 0, z * grassSpacing));
      }
   }

   glCreateVertexArrays(1, &renderData.VAO);

   //Reset buffers
   glDeleteBuffers(1, &renderData.PointsBuffer);
   glCreateBuffers(1, &renderData.PointsBuffer);

   //Create vertex buffer.
   glNamedBufferStorage(
      renderData.PointsBuffer,
      renderData.Points.size() * sizeof(glm::vec3),
      &renderData.Points[0],
      0);

   glVertexArrayVertexBuffer(
      renderData.VAO,
      0,
      renderData.PointsBuffer,
      0,
      sizeof(glm::vec3));

   glVertexArrayAttribFormat(
      renderData.VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderData.VAO, 0, 0);
   glEnableVertexArrayAttrib(renderData.VAO, 0);

   //CreateNoiseTexture(renderData);
}

void GrassRenderer::CreateNoiseTexture(GrassRenderData& renderData)
{
   Debug::CheckErrors();
   const Bitmap noiseBitmap = IO::ReadBitmap(IO::GetExecutablePath() + "Resources\\Textures\\white_noise.png");

   glCreateTextures(GL_TEXTURE_2D, 1, &renderData.NoiseTexture);
   glTextureStorage2D(renderData.NoiseTexture, 1, GL_RGB32F, noiseBitmap.Width, noiseBitmap.Height);
   glTextureSubImage2D(
      renderData.NoiseTexture,
      0,
      0, 0,
      noiseBitmap.Width, noiseBitmap.Height,
      GL_RGB,
      GL_FLOAT,
      &noiseBitmap.Data[0]);
   Debug::CheckErrors();

   //glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_BASE_LEVEL, 0);
   //glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_MAX_LEVEL, 8);
   //glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   //glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //GLfloat maxAnisotropy;
   //glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
   //glTextureParameterf(renderData.NoiseTexture, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

   //glGenerateTextureMipmap(renderData.NoiseTexture);

   glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTextureParameteri(renderData.NoiseTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
}

void GrassRenderer::Dispose(GrassRenderData& renderData)
{
   glDeleteVertexArrays(1, &renderData.VAO);
   glDeleteBuffers(1, &renderData.PointsBuffer);
}
