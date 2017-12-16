#include "ProspectEngine_pch.h"

#include "Shader.h"

#include "Renderer/RendererDefines.h"
#include "Renderer/Pipeline/ShaderStages/VertexShaderStage.h"
#include "Renderer/Pipeline/ShaderStages/TessControlShaderStage.h"
#include "Renderer/Pipeline/ShaderStages/TessEvaluationShaderStage.h"
#include "Renderer/Pipeline/ShaderStages/GeometryShaderStage.h"
#include "Renderer/Pipeline/ShaderStages/FragmentShaderStage.h"

using namespace Prospect;

Shader::Shader(
   const std::string& vertexShader,
   const std::string& fragmentShader)
   :
   m_program(GL_NULL)
{
   AddVertexShader(vertexShader);
   AddFragmentShader(fragmentShader);

   Compile();
}

Shader::Shader(
   const std::string& vertexShader,
   const std::string& tessControlShader,
   const std::string& tessEvaluationShader,
   const std::string& fragmentShader)
   :
   m_program(GL_NULL)
{
   AddVertexShader(vertexShader);
   AddTessControlShader(tessControlShader);
   AddTessEvaluationShader(tessEvaluationShader);
   AddFragmentShader(fragmentShader);

   Compile();
}

Shader::~Shader()
{
   glDeleteProgram(m_program);
}

bool Shader::operator==(const Shader &other) const
{
   return
      AreEqual(m_vertexShader.get(), other.m_vertexShader.get()) &&
      AreEqual(m_tessControlShader.get(), other.m_tessControlShader.get()) &&
      AreEqual(m_tessEvaluationShader.get(), other.m_tessEvaluationShader.get()) &&
      AreEqual(m_geometryShader.get(), other.m_geometryShader.get()) &&
      AreEqual(m_fragmentShader.get(), other.m_fragmentShader.get());
}

bool Shader::AreEqual(ShaderStage* lhs, ShaderStage* rhs) const
{
   if (lhs != nullptr && rhs != nullptr)
   {
      return lhs->GetName() == rhs->GetName();
   }

   return lhs == rhs;
}

void Shader::AddVertexShader(const std::string& shaderName)
{
   m_vertexShader = std::make_unique<VertexShaderStage>(shaderName);
}

void Shader::AddTessControlShader(const std::string& shaderName)
{
   m_tessControlShader = std::make_unique<TessControlShaderStage>(shaderName);
}

void Shader::AddTessEvaluationShader(const std::string& shaderName)
{
   m_tessEvaluationShader = std::make_unique<TessEvaluationShaderStage>(shaderName);
}

void Shader::AddGeometryShader(const std::string& shaderName)
{
   m_geometryShader = std::make_unique<GeometryShaderStage>(shaderName);
}

void Shader::AddFragmentShader(const std::string& shaderName)
{
   m_fragmentShader = std::make_unique<FragmentShaderStage>(shaderName);
}

bool Shader::CompileAndAttachShader(
   const GLuint program,
   const std::unique_ptr<ShaderStage>& shader)
{
   if (shader)
   {
      if(shader->Compile())
      {
         glAttachShader(program, shader->GetID());
      }
      else
      {
         //Failed to compile.
         return false;
      }
   }
   return true; //No error has occured, just a null shader.
}

bool Shader::Compile()
{
   m_program = glCreateProgram();

   bool success = true;

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

bool Shader::LinkProgram(const GLuint program)
{
   glLinkProgram(program);

   return ValidateProgram(program);
}

bool Shader::ValidateProgram(const GLuint program)
{
   //Get error.
   GLint success = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &success);

   if (success == GL_FALSE)
   {
      GLint logLength;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

      std::vector<GLchar> logText(logLength);
      glGetProgramInfoLog(program, logLength, &logLength, &logText[0]);

      std::cerr << "Error: Failed to link program: ";
      for (auto c : logText)
      {
         std::cerr << c;
      }
      std::cerr << std::endl;

      return false;
   }

   return true;
}

void Shader::Bind() const
{
   glUseProgram(m_program);
}

GLint Shader::GetUniformLocation(const std::string& uniform) const
{
   return glGetUniformLocation(m_program, uniform.c_str());
}

GLuint Shader::GetProgram() const
{
   return m_program;
}

