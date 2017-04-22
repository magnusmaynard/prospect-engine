#pragma once
#include "BaseShader.h"

class GeometryShader : public BaseShader
{
public:
   GeometryShader(const std::string& fileName)
      :
      BaseShader(fileName + ".gs", GL_GEOMETRY_SHADER)
   {
   }
};
