#include "ProspectEngine_pch.h"

#include "TessControlShaderStage.h"

using namespace Prospect;

TessControlShaderStage::TessControlShaderStage(const std::string& fileName):
   ShaderStage(fileName, GL_TESS_CONTROL_SHADER)
{
}
