#include "ProspectEngine_pch.h"


#include "Framebuffer.h"

using namespace Prospect;

Framebuffer::Framebuffer(const glm::ivec2 & size)
   :
   m_size(size)
{
   Initialize();
}

Framebuffer::~Framebuffer()
{
   Destroy();
}

void Framebuffer::Bind()
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
   glViewport(0, 0, m_size.x, m_size.y);
}

void Framebuffer::Initialize()
{
   glCreateFramebuffers(1, &m_FBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void Framebuffer::Destroy()
{
   glDeleteFramebuffers(1, &m_FBO);
}

void Framebuffer::Resize(const glm::ivec2& size)
{
   m_size = size;

   Destroy();
   Initialize();
}
void Framebuffer::Validate()
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
   const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (error != GL_FRAMEBUFFER_COMPLETE)
   {
      std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   }
}

GLuint Framebuffer::GetName() const
{
   return m_FBO;
}

glm::ivec2 Framebuffer::GetSize() const
{
   return m_size;
}
