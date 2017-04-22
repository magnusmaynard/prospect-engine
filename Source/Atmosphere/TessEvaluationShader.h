#pragma once
#include "BaseShader.h"

class TessEvaluationShader : public BaseShader
{
public:
   TessEvaluationShader(const std::string& fileName)
      :
      BaseShader(fileName + ".tes", GL_TESS_EVALUATION_SHADER)
   {
   }
};
