#include "ProspectEngine_pch.h"

#include "Shader.h"

#include "Renderer/RendererDefines.h"
#include "VertexShader.h"
#include "TessControlShader.h"
#include "TessEvaluationShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"

using namespace Prospect;

Shader::Shader()
   :
   m_program(GL_NULL)
{
}

Shader::~Shader()
{
   glDeleteProgram(m_program);
}

Shader::Shader(Shader&& other)
   :
   m_program(other.m_program),
   m_vertexShader(move(other.m_vertexShader)),
   m_tessControlShader(move(other.m_tessControlShader)),
   m_tessEvaluationShader(move(other.m_tessEvaluationShader)),
   m_geometryShader(move(other.m_geometryShader)),
   m_fragmentShader(move(other.m_fragmentShader))
{
   //Release.
   other.m_program = GL_NULL;
   other.m_vertexShader = nullptr;
   other.m_tessControlShader = nullptr;
   other.m_tessEvaluationShader = nullptr;
   other.m_geometryShader = nullptr;
   other.m_fragmentShader = nullptr;
}

Shader& Shader::operator=(Shader&& other)
{
   if (this != &other)
   {
      //Move
      m_program = other.m_program;
      m_vertexShader = move(other.m_vertexShader);
      m_tessControlShader = move(other.m_tessControlShader);
      m_tessEvaluationShader = move(other.m_tessEvaluationShader);
      m_geometryShader = move(other.m_geometryShader);
      m_fragmentShader = move(other.m_fragmentShader);

      //Release
      other.m_program = GL_NULL;
      other.m_vertexShader = nullptr;
      other.m_tessControlShader = nullptr;
      other.m_tessEvaluationShader = nullptr;
      other.m_geometryShader = nullptr;
      other.m_fragmentShader = nullptr;
   }

   return *this;
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

bool Shader::AreEqual(BaseShader* lhs, BaseShader* rhs) const
{
   if (lhs != nullptr && rhs != nullptr)
   {
      return lhs->GetName() == rhs->GetName();
   }

   return lhs == rhs;
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

void Shader::AddVertexShader(const std::string& fileName)
{
   m_vertexShader = std::make_unique<VertexShader>(fileName);
}

void Shader::AddTessControlShader(const std::string& fileName)
{
   m_tessControlShader = std::make_unique<TessControlShader>(fileName);
}

void Shader::AddTessEvaluationShader(const std::string& fileName)
{
   m_tessEvaluationShader = std::make_unique<TessEvaluationShader>(fileName);
}

void Shader::AddGeometryShader(const std::string& fileName)
{
   m_geometryShader = std::make_unique<GeometryShader>(fileName);
}

void Shader::AddFragmentShader(const std::string& fileName)
{
   m_fragmentShader = std::make_unique<FragmentShader>(fileName);
}

bool Shader::CompileAndAttachShader(
   const GLuint program,
   const std::unique_ptr<BaseShader>& shader)
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

