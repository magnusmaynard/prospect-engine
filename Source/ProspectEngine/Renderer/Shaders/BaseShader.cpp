#include "ProspectEngine_pch.h"

#include "BaseShader.h"

#include "Resources/ResourceIO.h"

using namespace Prospect;

BaseShader::BaseShader(const std::string& fileName, GLenum type)
   :
   m_fileName(fileName),
   m_type(type)
{
}

BaseShader::~BaseShader()
{
   glDeleteShader(m_id);
}

GLuint BaseShader::GetID() const
{
   return m_id;
}

std::string BaseShader::GetName() const
{
   return m_fileName;
}

bool BaseShader::Compile()
{
   //Read from file.
   auto data = ResourceIO::ReadText(m_fileName);

   const GLchar* sourceChars = data.c_str();
   const GLint sourceLength = static_cast<GLint>(data.length());

   //Compile.
   m_id = glCreateShader(m_type);
   glShaderSource(m_id, 1, &sourceChars, &sourceLength);
   glCompileShader(m_id);

   //Validate.
   GLint success = 0;
   glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

   //Log errors.
   if (success == GL_FALSE)
   {
      GLint logLength;
      glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

      std::vector<GLchar> logText(logLength);
      glGetShaderInfoLog(m_id, logLength, &logLength, &logText[0]);

      std::cout << "Error compiling shader : " << m_fileName << " : ";
      for (auto c : logText)
      {
         std::cout << c;
      }
      std::cout << std::endl;

      return false;
   }

   return true;
}
