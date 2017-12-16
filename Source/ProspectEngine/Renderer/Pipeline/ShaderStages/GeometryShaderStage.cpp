#include "ProspectEngine_pch.h"

#include "GeometryShaderStage.h"

using namespace Prospect;

GeometryShaderStage::GeometryShaderStage(const std::string& fileName):
   ShaderStage(fileName, GL_GEOMETRY_SHADER)
{
}
