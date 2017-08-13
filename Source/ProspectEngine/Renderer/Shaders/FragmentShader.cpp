#include "FragmentShader.h"

using namespace Prospect;

FragmentShader::FragmentShader(const std::string& fileName):
   BaseShader(fileName + ".fs", GL_FRAGMENT_SHADER)
{
}
