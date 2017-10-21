#pragma once

#include "BaseShader.h"

namespace Prospect
{
   class Shader
   {
   public:
      Shader();
      ~Shader();
      Shader(Shader&& other);
      Shader& operator=(Shader&& other);
      Shader(const Shader& other) = delete;
      Shader& operator=(const Shader& other) = delete;

      bool operator ==(const Shader &other) const;

      void AddVertexShader(const std::string& fileName);
      void AddTessControlShader(const std::string& fileName);
      void AddTessEvaluationShader(const std::string& fileName);
      void AddGeometryShader(const std::string& fileName);
      void AddFragmentShader(const std::string& fileName);

      bool Compile();

      void Bind() const;
      GLint GetUniformLocation(const std::string& uniform) const;
      GLuint GetProgram() const;

   private:
      bool AreEqual(BaseShader* lhs, BaseShader* rhs) const;

      GLuint m_program;

      std::unique_ptr<BaseShader> m_vertexShader;
      std::unique_ptr<BaseShader> m_tessControlShader;
      std::unique_ptr<BaseShader> m_tessEvaluationShader;
      std::unique_ptr<BaseShader> m_geometryShader;
      std::unique_ptr<BaseShader> m_fragmentShader;

      static bool Shader::CompileAndAttachShader(
         const GLuint program,
         const std::unique_ptr<BaseShader>& shader);

      static bool LinkProgram(const GLuint& program);
   };
}
