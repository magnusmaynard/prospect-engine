#pragma once
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Renderer/Pipeline/Shaders/LightingShader.h"
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"
#include "Renderer/Pipeline/Shaders/TextShader.h"
#include "Renderer/Pipeline/Shaders/TerrainShader.h"
#include "Renderer/Pipeline/Shaders/SunShader.h"
#include "Renderer/Pipeline/Shaders/AtmosphereShader.h"
#include "Renderer/Pipeline/Shaders/DebugShader.h"
#include "Renderer/Pipeline/Shaders/GrassShader.h"

namespace Prospect
{
   class ShaderLibrary
   {
   public:
      ShaderLibrary(const GlobalUniformBuffers& globalUniforms);

      LightingShader& GetLightingShader();
      BlinnPhongShader& GetBlinnPhongShader();
      TextShader& GetTextShader();
      TerrainShader& GetTerrainShader();
      GrassShader& GetGrassShader();
      SunShader& GetSunShader();
      AtmosphereShader& GetAtmosphereShader();
      DebugShader& GetDebugShader();

   private:
      LightingShader m_lightingShader;
      BlinnPhongShader m_blinnShader;
      TextShader m_textShader;
      TerrainShader m_terrainShader;
      GrassShader m_grassShader;
      SunShader m_sunShader;
      AtmosphereShader m_scatteringShader;
      DebugShader m_debugShader;
   };
}
