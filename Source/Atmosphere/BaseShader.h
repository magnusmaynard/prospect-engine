#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class BaseShader
{
public:
   BaseShader(const std::string& fileName, GLenum type);
   GLuint Compile() const;
private:
   std::string m_fileName;
   GLenum m_type;
};
