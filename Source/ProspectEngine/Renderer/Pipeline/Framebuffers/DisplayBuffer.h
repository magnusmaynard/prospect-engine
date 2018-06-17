#pragma once
#include "Renderer/Pipeline/Framebuffers/Framebuffer.h"

namespace Prospect
{
   class DisplayBuffer
   {
   public:
      DisplayBuffer(const glm::ivec2& size);
      ~DisplayBuffer();

      void Resize(const glm::ivec2& size);
      void Clear();
      void Bind();

      void CopyTo(const GLuint framebuffer);

      GLuint GetDisplayTexture() const;
      GLuint GetFramebufferName() const;
      
   private:
      void Initialize();
      void Destroy();

      Framebuffer m_framebuffer;
      GLuint m_texture;
   };
}
