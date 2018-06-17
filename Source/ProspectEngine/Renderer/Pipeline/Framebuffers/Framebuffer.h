#pragma once

namespace Prospect
{
   enum class FramebufferAttachment
   {
      Color0 = GL_COLOR_ATTACHMENT0,
      Color1 = GL_COLOR_ATTACHMENT1,
      Color2 = GL_COLOR_ATTACHMENT2,
      Depth = GL_DEPTH_ATTACHMENT,
   };

   class Framebuffer
   {
   public:
      Framebuffer(const glm::ivec2& size);
      ~Framebuffer();

      void Resize(const glm::ivec2& size);
      void Bind();
      void Validate();

      GLuint GetName() const;
      glm::ivec2 GetSize() const;

   private:
      void Initialize();
      void Destroy();

      GLuint m_FBO;
      glm::ivec2 m_size;
   };
}
