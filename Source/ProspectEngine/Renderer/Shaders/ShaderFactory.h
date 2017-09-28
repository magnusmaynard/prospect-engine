#pragma once
#include "Shader.h"
#include <deque>

namespace Prospect
{
   class ShaderFactory
   {
   public:
      Shader& CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

   private:
      Shader& AddShaderIfDoesNotExist(Shader& newShader);

      std::deque<Shader> m_shaders;
   };
}
