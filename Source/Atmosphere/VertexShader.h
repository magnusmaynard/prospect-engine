#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
   VertexShader(const std::string& fileName)
      :
      BaseShader(fileName + ".vs", GL_VERTEX_SHADER)
   {
   }
};
