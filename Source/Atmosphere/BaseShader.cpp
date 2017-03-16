#include "BaseShader.h"

#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream>

BaseShader::BaseShader(const std::string& fileName, GLenum type)
   :
   m_fileName(fileName),
   m_type(type)
{
}

GLuint BaseShader::Compile() const
{
   //Read from file
   std::string sourcePath = "ShaderFiles/" + m_fileName; //TODO: Copy shaders to bin folder.
   std::ifstream sourceFile(sourcePath);
   std::stringstream sourceStream;
   sourceStream << sourceFile.rdbuf();
   auto sourceString = sourceStream.str();

   const GLchar* sourceChars = sourceString.c_str();
   const GLint sourceLength = sourceString.length();

   //Compile
   GLuint shader = glCreateShader(m_type);
   glShaderSource(shader, 1, &sourceChars, &sourceLength);
   glCompileShader(shader);

   //Validate
   GLint success = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

   if (success == GL_FALSE)
   {
      GLint logLength;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

      std::vector<GLchar> logText(logLength);
      glGetShaderInfoLog(shader, logLength, &logLength, &logText[0]);

      std::cout << "Error compiling shader : " << m_fileName << " : ";

      for (auto c : logText)
      {
         std::cout << c;
      }

      std::cout << std::endl;
   }

   return shader;
}