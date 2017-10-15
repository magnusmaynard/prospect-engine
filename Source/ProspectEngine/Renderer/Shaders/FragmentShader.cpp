#include "ProspectEngine_pch.h"

#include "FragmentShader.h"

using namespace Prospect;

FragmentShader::FragmentShader(const std::string& fileName):
   BaseShader(fileName, GL_FRAGMENT_SHADER)
{
}
