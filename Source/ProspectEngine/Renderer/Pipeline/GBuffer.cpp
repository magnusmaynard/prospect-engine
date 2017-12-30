#include "ProspectEngine_pch.h"

#include "GBuffer.h"
#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;

GBuffer::GBuffer(ShaderLibrary& shaderLibrary, const glm::ivec2& size)
   :
   m_shader(shaderLibrary.GetGBufferShader())
{
   Initialize(size);
}

GBuffer::~GBuffer()
{
   Destroy();
}

void GBuffer::Initialize(const glm::ivec2& size)
{
   glCreateFramebuffers(1, &m_FBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

   glCreateTextures(GL_TEXTURE_2D, G_TEXTURE_COUNT, &m_textures[0]);

   //Albedo
   glTextureStorage2D(m_textures[G_TEXTURE_ALBEDO], 1, GL_RGBA32F, size.x, size.y);
   glTextureParameteri(m_textures[G_TEXTURE_ALBEDO], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_ALBEDO], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   //Normal
   glTextureStorage2D(m_textures[G_TEXTURE_NORMAL], 1, GL_RGBA32F, size.x, size.y);
   glTextureParameteri(m_textures[G_TEXTURE_NORMAL], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_NORMAL], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   //Specular
   glTextureStorage2D(m_textures[G_TEXTURE_SPECULAR], 1, GL_RGBA32F, size.x, size.y);
   glTextureParameteri(m_textures[G_TEXTURE_SPECULAR], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_SPECULAR], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   //Depth
   glTextureStorage2D(m_textures[G_TEXTURE_DEPTH], 1, GL_DEPTH_COMPONENT32F, size.x, size.y);

   //Attached textures
   glNamedFramebufferTexture(m_FBO, GL_COLOR_ATTACHMENT0, m_textures[G_TEXTURE_ALBEDO], 0);
   glNamedFramebufferTexture(m_FBO, GL_COLOR_ATTACHMENT1, m_textures[G_TEXTURE_NORMAL], 0);
   glNamedFramebufferTexture(m_FBO, GL_COLOR_ATTACHMENT2, m_textures[G_TEXTURE_SPECULAR], 0);
   glNamedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, m_textures[G_TEXTURE_DEPTH], 0);

   const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (error != GL_FRAMEBUFFER_COMPLETE)
   {
      std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   }
}

void GBuffer::Destroy()
{
   glDeleteTextures(G_TEXTURE_COUNT, &m_textures[0]);
   glDeleteFramebuffers(1, &m_FBO);
}

void GBuffer::Resize(const glm::ivec2& size)
{
   Destroy();
   Initialize(size);
}

void GBuffer::Clear()
{
   static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,  GL_COLOR_ATTACHMENT2 };
   static const int drawBuffersCount = 3;
   static GLfloat zeros[] = { 0, 0, 0, 0 };
   static GLfloat ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };

   glNamedFramebufferDrawBuffers(m_FBO, drawBuffersCount, drawBuffers);

   glClearNamedFramebufferfv(m_FBO, GL_COLOR, 0, zeros);
   glClearNamedFramebufferfv(m_FBO, GL_COLOR, 1, zeros);
   glClearNamedFramebufferfv(m_FBO, GL_COLOR, 2, zeros);
   glClearNamedFramebufferfv(m_FBO, GL_DEPTH, 0, ones);
}

void GBuffer::Bind()
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void GBuffer::Present()
{
   glDisable(GL_DEPTH_TEST);

   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   glDrawBuffer(GL_BACK);
   glBindTextureUnit(0, m_textures[G_TEXTURE_ALBEDO]);
   glBindTextureUnit(1, m_textures[G_TEXTURE_NORMAL]);
   glBindTextureUnit(2, m_textures[G_TEXTURE_SPECULAR]);
   glBindTextureUnit(3, m_textures[G_TEXTURE_DEPTH]);

   m_shader.Bind();

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
