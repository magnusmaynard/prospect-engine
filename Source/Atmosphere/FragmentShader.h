#pragma once
#include "BaseShader.h"

class FragmentShader : public BaseShader
{
public:
   FragmentShader(const std::string& fileName)
      :
      BaseShader(fileName, GL_FRAGMENT_SHADER)
   {
   }
};
