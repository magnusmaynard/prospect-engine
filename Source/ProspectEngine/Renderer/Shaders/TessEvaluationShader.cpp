#include "TessEvaluationShader.h"

using namespace Prospect;

TessEvaluationShader::TessEvaluationShader(const std::string& fileName):
   BaseShader(fileName + ".tes", GL_TESS_EVALUATION_SHADER)
{
}