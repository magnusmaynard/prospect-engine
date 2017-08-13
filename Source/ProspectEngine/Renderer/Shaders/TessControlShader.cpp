#include "TessControlShader.h"

using namespace Prospect;

TessControlShader::TessControlShader(const std::string& fileName):
   BaseShader(fileName + ".tcs", GL_TESS_CONTROL_SHADER)
{
}
