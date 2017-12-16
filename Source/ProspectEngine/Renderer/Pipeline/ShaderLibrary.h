#pragma once
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Renderer/Pipeline/Shaders/BlinnShader.h"
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

      BlinnShader& GetBlinnShader();
      TextShader& GetTextShader();
      TerrainShader& GetTerrainShader();
      SunShader& GetSunShader();
      ScatteringShader& GetScatteringShader();

   private:
      BlinnShader m_blinnShader;
      TextShader m_textShader;
      TerrainShader m_terrainShader;
      SunShader m_sunShader;
      ScatteringShader m_scatteringShader;
   };
}
