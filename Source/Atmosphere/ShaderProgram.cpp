#include "ShaderProgram.h"

#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram(
   const std::string& vertexShaderFile,
   const std::string& fragmentShaderFile)
   :
   m_vertexShader(std::make_unique<VertexShader>(vertexShaderFile)),
   m_fragmentShader(std::make_unique<FragmentShader>(fragmentShaderFile))
{
   m_program = Compile();
}

ShaderProgram::~ShaderProgram()
{
   glDeleteProgram(m_program);
}

GLuint ShaderProgram::Compile() const
{
   GLuint program = glCreateProgram();
   GLuint vertexShader, fragmentShader;

   if (m_vertexShader)
   {
      vertexShader = m_vertexShader->Compile();
      glAttachShader(program, vertexShader);
   }

   if (m_fragmentShader)
   {
      fragmentShader = m_fragmentShader->Compile();
      glAttachShader(program, fragmentShader);
   }

   glLinkProgram(program);
   Check(program, GL_LINK_STATUS, "Error linking program.");

   if (m_vertexShader)
   {
      glDeleteShader(vertexShader);
   }

   if (m_fragmentShader)
   {
      glDeleteShader(fragmentShader);
   }

   return program;
}

void ShaderProgram::Check(const GLuint& program, const GLenum& parameter, const std::string& message)
{
   GLint success = 0;
   glGetProgramiv(program, parameter, &success);

   if (success == GL_FALSE)
   {
      GLint logLength;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

      std::vector<GLchar> logText(logLength);
      glGetProgramInfoLog(program, logLength, &logLength, &logText[0]);

      std::cout << message << " : ";
      for (auto c : logText)
         std::cout << c;
      std::cout << std::endl;
   }
}

void ShaderProgram::Use() const
{
   glUseProgram(m_program);
}

GLint ShaderProgram::GetUniformLocation(const std::string& uniform) const
{
   return glGetUniformLocation(m_program, uniform.c_str());
}
