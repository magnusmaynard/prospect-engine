#include "ProspectEngine_pch.h"

#include "ShaderLibrary.h"

using namespace Prospect;

ShaderLibrary::ShaderLibrary(const GlobalUniformBuffers& globalUniforms)
   :
   m_blinnShader(globalUniforms),
   m_textShader(globalUniforms),
   m_terrainShader(globalUniforms),
   m_sunShader(globalUniforms),
   m_scatteringShader(globalUniforms)
{
}

BlinnShader& ShaderLibrary::GetBlinnShader()
{
   return m_blinnShader;
}

TextShader& ShaderLibrary::GetTextShader()
{
   return m_textShader;
}

TerrainShader& ShaderLibrary::GetTerrainShader()
{
   return m_terrainShader;
}

SunShader& ShaderLibrary::GetSunShader()
{
   return m_sunShader;
}

ScatteringShader& ShaderLibrary::GetScatteringShader()
{
   return m_scatteringShader;
}
