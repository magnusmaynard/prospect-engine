#include "ProspectEngine_pch.h"

#include "EffectsBuffer.h"

using namespace Prospect;

EffectsBuffer::EffectsBuffer(const glm::ivec2& size)
   :
   m_framebuffer(size)
{
   Initialize();
}

EffectsBuffer::~EffectsBuffer()
{
   Destroy();
}

void EffectsBuffer::Resize(const glm::ivec2& size)
{
   m_framebuffer.Resize(size);

   Destroy();
   Initialize();
}

void EffectsBuffer::Clear()
{
   static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
   static const int drawBuffersCount = 1;
   static GLfloat zeros[] = { 0, 0, 0, 0 };

   const GLuint fboName = m_framebuffer.GetName();

   glNamedFramebufferDrawBuffers(fboName, drawBuffersCount, drawBuffers);

   glClearNamedFramebufferfv(fboName, GL_COLOR, 0, zeros);
}

void EffectsBuffer::Bind()
{
   m_framebuffer.Bind();
}

void EffectsBuffer::CopyTo(const GLuint framebuffer)
{
   const auto size = m_framebuffer.GetSize();

   glBlitNamedFramebuffer(
      m_framebuffer.GetName(),
      framebuffer,
      0, 0, size.x, size.y,
      0, 0, size.x, size.y,
      GL_COLOR_BUFFER_BIT,
      GL_NEAREST);
}

GLuint EffectsBuffer::GetEffectsTexture() const
{
   return m_texture;
}

GLuint EffectsBuffer::GetFramebufferName() const
{
   return m_framebuffer.GetName();
}

void EffectsBuffer::Initialize()
{
   m_framebuffer.Bind();

   glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

   const glm::ivec2 fboSize = m_framebuffer.GetSize();
   glTextureStorage2D(m_texture, 1, GL_RGBA32F, fboSize.x, fboSize.y);
   glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glNamedFramebufferTexture(m_framebuffer.GetName(), GL_COLOR_ATTACHMENT0, m_texture, 0);

   m_framebuffer.Validate();
}

void EffectsBuffer::Destroy()
{
   glDeleteTextures(1, &m_texture);
}