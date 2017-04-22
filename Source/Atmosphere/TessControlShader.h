#pragma once
#include "BaseShader.h"

class TessControlShader : public BaseShader
{
public:
   TessControlShader(const std::string& fileName)
      :
      BaseShader(fileName + ".tcs", GL_TESS_CONTROL_SHADER)
   {
   }
};
