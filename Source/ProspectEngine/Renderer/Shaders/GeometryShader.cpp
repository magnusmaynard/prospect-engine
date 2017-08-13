#include "GeometryShader.h"

using namespace Prospect;

GeometryShader::GeometryShader(const std::string& fileName):
   BaseShader(fileName + ".gs", GL_GEOMETRY_SHADER)
{
}
