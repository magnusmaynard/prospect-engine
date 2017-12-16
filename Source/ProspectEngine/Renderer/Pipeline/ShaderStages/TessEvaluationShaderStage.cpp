#include "ProspectEngine_pch.h"

#include "TessEvaluationShaderStage.h"

using namespace Prospect;

TessEvaluationShaderStage::TessEvaluationShaderStage(const std::string& fileName):
   ShaderStage(fileName, GL_TESS_EVALUATION_SHADER)
{
}
