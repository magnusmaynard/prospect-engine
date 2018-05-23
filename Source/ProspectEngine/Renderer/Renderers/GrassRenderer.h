﻿#pragma once
#include "RenderDataLibrary.h"
#include "Renderer/Pipeline/Shaders/GrassShader.h"

namespace Prospect
{
   class ShaderLibrary;

   struct GrassRenderData
   {
      bool Initialised;
      GLuint VAO;
      GLuint PointsBuffer;
      std::vector<glm::vec3> Points;
      float PatchSize;
      int PatchGrassRows;
   };

   struct TerrainRenderData;
   class Terrain_impl;

   class GrassRenderer
   {
   public:
      GrassRenderer(ShaderLibrary& shaderLibrary);
      ~GrassRenderer();

      void Render(const Terrain_impl& terrain, const TerrainRenderData& terrainRenderData);

   private:
      static void Initialise(GrassRenderData& renderData);
      static void Dispose(GrassRenderData& renderData);

      GrassShader& m_shader;
      RenderDataLibrary<GrassRenderData> m_renderDataLibrary;
   };
}
