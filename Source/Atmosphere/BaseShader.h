#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Prospect
{
   class BaseShader
   {
   public:
      BaseShader(const std::string& fileName, GLenum type);
      ~BaseShader();
      bool Compile();

      GLuint GetID() const;

   private:
      const std::string m_extension = ".glsl";

      const std::string m_fileName;
      const GLenum m_type;

      GLuint m_id = -1;
   };
}
