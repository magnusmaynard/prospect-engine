#pragma once

#include <string>
#include <memory>
#include "BaseShader.h"

namespace Prospect
{
   class ShaderProgram
   {
   public:
      ShaderProgram();
      ~ShaderProgram();
      ShaderProgram(ShaderProgram&& other);
      ShaderProgram& operator=(ShaderProgram&& other);
      ShaderProgram(const ShaderProgram& other) = delete;
      ShaderProgram& operator=(const ShaderProgram& other) = delete;

      void AddVertexShader(const std::string& fileName);
      void AddTessControlShader(const std::string& fileName);
      void AddTessEvaluationShader(const std::string& fileName);
      void AddGeometryShader(const std::string& fileName);
      void AddFragmentShader(const std::string& fileName);

      bool Compile();

      void Use() const;
      GLint GetUniformLocation(const std::string& uniform) const;

   private:
      GLuint m_program = 0;

      std::unique_ptr<BaseShader> m_vertexShader;
      std::unique_ptr<BaseShader> m_tessControlShader;
      std::unique_ptr<BaseShader> m_tessEvaluationShader;
      std::unique_ptr<BaseShader> m_geometryShader;
      std::unique_ptr<BaseShader> m_fragmentShader;

      static bool ShaderProgram::CompileAndAttachShader(
         const GLuint program,
         const std::unique_ptr<BaseShader>& shader);

      static bool LinkProgram(const GLuint& program);
   };
}
