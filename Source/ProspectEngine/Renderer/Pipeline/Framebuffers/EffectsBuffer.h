#pragma once
#include "Renderer/Pipeline/Framebuffers/Framebuffer.h"

namespace Prospect
{
   class EffectsBuffer
   {
   public:
      EffectsBuffer(const glm::ivec2& size);
      ~EffectsBuffer();

      void Resize(const glm::ivec2& size);
      void Clear();
      void Bind();

      void CopyTo(const GLuint framebuffer);

      GLuint GetEffectsTexture() const;
      GLuint GetFramebufferName() const;

   private:
      void Initialize();
      void Destroy();

      Framebuffer m_framebuffer;
      GLuint m_texture;
   };
}
