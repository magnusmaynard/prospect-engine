#pragma once
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Renderer/Pipeline/Shaders/GBufferShader.h"
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"
#include "Renderer/Pipeline/Shaders/TextShader.h"
#include "Renderer/Pipeline/Shaders/TerrainShader.h"
#include "Renderer/Pipeline/Shaders/SunShader.h"
#include "Renderer/Pipeline/Shaders/ScatteringShader.h"

namespace Prospect
{
   class ShaderLibrary
   {
   public:
      ShaderLibrary(const GlobalUniformBuffers& globalUniforms);

      GBufferShader& GetGBufferShader();
      BlinnPhongShader& GetBlinnPhongShader();
      TextShader& GetTextShader();
      TerrainShader& GetTerrainShader();
      SunShader& GetSunShader();
      ScatteringShader& GetScatteringShader();

   private:
      GBufferShader m_gBufferShader;
      BlinnPhongShader m_blinnShader;
      TextShader m_textShader;
      TerrainShader m_terrainShader;
      SunShader m_sunShader;
      ScatteringShader m_scatteringShader;
   };
}
