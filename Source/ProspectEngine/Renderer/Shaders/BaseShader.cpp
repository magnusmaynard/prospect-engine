#include "BaseShader.h"

#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace Prospect;

BaseShader::BaseShader(const std::string& fileName, GLenum type)
   :
   m_fileName(fileName + m_extension),
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

bool BaseShader::Compile()
{
   //Read from file.
   std::string sourcePath = "ShaderFiles/" + m_fileName; //TODO: Copy shaders to bin folder.
   std::ifstream sourceFile(sourcePath);
   std::stringstream sourceStream;
   sourceStream << sourceFile.rdbuf();
   auto sourceString = sourceStream.str();

   const GLchar* sourceChars = sourceString.c_str();
   const GLint sourceLength = sourceString.length();

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
