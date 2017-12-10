#pragma once
#include "Shader.h"
#include <deque>

namespace Prospect
{
   class ShaderFactory
   {
   public:
      static Shader& CreateBlinnPhongShader();

      static Shader& CreateShader(
         const std::string& vertexShader,
         const std::string& fragmentShader);

      static Shader& CreateShader(
         const std::string& vertexShader,
         const std::string& tessControlShader,
         const std::string& tessEvaluationShader,
         const std::string& fragmentShader);

   private:
      static Shader& AddShaderIfUnique(Shader& newShader);

      static std::deque<Shader> m_shaders;
   };
}
