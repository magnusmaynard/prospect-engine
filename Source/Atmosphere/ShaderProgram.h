#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include <string>
#include <memory>

class ShaderProgram
{
public:
   ShaderProgram(
      const std::string& vertexShaderFile,
      const std::string& fragmentShaderFile);
   ~ShaderProgram();
   void Use() const;
   GLint GetUniformLocation(const std::string& uniform) const;
private:
   GLuint Compile() const;
   static void Check(const GLuint& program, const GLenum& parameter, const std::string& message);

   GLuint m_program;
   std::unique_ptr<VertexShader> m_vertexShader;
   std::unique_ptr<FragmentShader> m_fragmentShader;
};