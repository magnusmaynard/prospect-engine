#include "ProspectEngine_pch.h"

#include "GrassRenderer.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Renderers/TerrainRenderer.h"

using namespace Prospect;

GrassRenderer::GrassRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetGrassShader())
{
   m_renderDataLibrary.SetInitialise(Initialise);
   m_renderDataLibrary.SetDispose(Dispose);
}

GrassRenderer::~GrassRenderer()
{
}

void GrassRenderer::Render(
   const Terrain_impl& terrain,
   const TerrainRenderData& terrainRenderData)
{
   GrassRenderData& renderData = m_renderDataLibrary.GetRenderData(terrain.GetId());

   m_shader.Bind();
   glBindTextureUnit(0, terrainRenderData.HeightMapTexture);
   glBindVertexArray(renderData.VAO);

   glDisable(GL_CULL_FACE);
   glDrawArrays(GL_POINTS, 0, renderData.Points.size());
}

void GrassRenderer::Initialise(GrassRenderData& renderData)
{
   renderData.PatchSize = 120.f;
   renderData.PatchGrassRows = 250;

   const int halfRows= static_cast<int>(renderData.PatchGrassRows * 0.5);
   const float grassSpacing = renderData.PatchSize / renderData.PatchGrassRows;

   //Create grid of points.
   renderData.Points.reserve(static_cast<int>(renderData.PatchSize * renderData.PatchSize));

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
}

void GrassRenderer::Dispose(GrassRenderData& renderData)
{
   glDeleteVertexArrays(1, &renderData.VAO);
   glDeleteBuffers(1, &renderData.PointsBuffer);
}
