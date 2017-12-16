#include "ProspectEngine_pch.h"

#include "FragmentShaderStage.h"

using namespace Prospect;

FragmentShaderStage::FragmentShaderStage(const std::string& fileName):
   ShaderStage(fileName, GL_FRAGMENT_SHADER)
{
}
