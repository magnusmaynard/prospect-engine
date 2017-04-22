#include "ShaderProgram.h"

#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
   glDeleteProgram(m_program);
}

void ShaderProgram::Add(const VertexShader& vertexShader)
{
   m_vertexShader = std::make_unique<BaseShader>(vertexShader);
}

void ShaderProgram::Add(const TessControlShader& tessControlShader)
{
   m_tessControlShader = std::make_unique<BaseShader>(tessControlShader);
}

void ShaderProgram::Add(const TessEvaluationShader& tessEvaluationShader)
{
   m_tessEvaluationShader = std::make_unique<BaseShader>(tessEvaluationShader);
}

void ShaderProgram::Add(const GeometryShader& geometryShader)
{
   m_geometryShader = std::make_unique<BaseShader>(geometryShader);
}

void ShaderProgram::Add(const FragmentShader& fragmentShader)
{
   m_fragmentShader = std::make_unique<BaseShader>(fragmentShader);
}

bool ShaderProgram::CompileAndAttachShader(
   const GLuint program,
   const std::unique_ptr<BaseShader>& shader)
{
   if (shader != nullptr)
   {
      if(shader->Compile() == false)
      {
         return false;
      }
      glAttachShader(program, shader->GetID());

   }
   return true; //No error has occured, just a null shader.
}

bool ShaderProgram::Compile()
{
   bool success = true;

   //Create program.
   m_program = glCreateProgram();

   //Compile and attach to program.
   success &= CompileAndAttachShader(m_program, m_vertexShader);
   success &= CompileAndAttachShader(m_program, m_tessControlShader);
   success &= CompileAndAttachShader(m_program, m_tessEvaluationShader);
   success &= CompileAndAttachShader(m_program, m_geometryShader);
   success &= CompileAndAttachShader(m_program, m_fragmentShader);

   //Link.
   if (success)
   {
      success &= LinkProgram(m_program);
   }

   return success;
}

bool ShaderProgram::LinkProgram(const GLuint& program)
{
   //Link program.
   glLinkProgram(program);

   //Get error.
   GLint success = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &success);

   //Log error.
   if (success == GL_FALSE)
   {
      GLint logLength;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

      std::vector<GLchar> logText(logLength);
      glGetProgramInfoLog(program, logLength, &logLength, &logText[0]);

      std::cout << "Error linking program. : ";
      for (auto c : logText)
      {
         std::cout << c;
      }
      std::cout << std::endl;

      return false;
   }

   return true;
}

void ShaderProgram::Use() const
{
   glUseProgram(m_program);
}

GLint ShaderProgram::GetUniformLocation(const std::string& uniform) const
{
   return glGetUniformLocation(m_program, uniform.c_str());
}
