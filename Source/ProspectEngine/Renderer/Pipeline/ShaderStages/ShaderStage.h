#pragma once
#include "Renderer/RendererDefines.h"

namespace Prospect
{
   class ShaderStage
   {
   public:
      ShaderStage(const std::string& fileName, GLenum type);
      ~ShaderStage();

      bool Compile();

      GLuint GetID() const;
      std::string GetName() const;

   private:
      bool ValidateShader() const;

      const std::string m_fileName;
      const GLenum m_type;

      GLuint m_id = GL_NULL;
   };
}
