#include "ProspectEngine_pch.h"

#include "TessControlShader.h"

using namespace Prospect;

TessControlShader::TessControlShader(const std::string& fileName):
   BaseShader(fileName, GL_TESS_CONTROL_SHADER)
{
}
