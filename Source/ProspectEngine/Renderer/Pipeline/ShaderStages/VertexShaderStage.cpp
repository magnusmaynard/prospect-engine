#include "ProspectEngine_pch.h"

#include "VertexShaderStage.h"

using namespace Prospect;

VertexShaderStage::VertexShaderStage(const std::string& fileName):
   ShaderStage(fileName, GL_VERTEX_SHADER)
{
}
