#include "VertexShader.h"

using namespace Prospect;

VertexShader::VertexShader(const std::string& fileName):
   BaseShader(fileName + ".vs", GL_VERTEX_SHADER)
{
}
