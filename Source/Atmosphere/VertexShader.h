#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
   VertexShader(const std::string& fileName)
      :
      BaseShader(fileName, GL_VERTEX_SHADER)
   {
   }
};
