#include "ProspectEngine_pch.h"

#include "GBuffer.h"
#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;

GBuffer::GBuffer(const glm::ivec2& size)
   :
   m_framebuffer(size)
{
   Initialize();
}

GBuffer::~GBuffer()
{
   Destroy();
}

void GBuffer::Initialize()
{
   m_framebuffer.Bind();

   glCreateTextures(GL_TEXTURE_2D, G_TEXTURE_COUNT, &m_textures[0]);

   const glm::ivec2 fboSize = m_framebuffer.GetSize();

   //Albedo
   glTextureStorage2D(m_textures[G_TEXTURE_ALBEDO], 1, GL_RGBA32F, fboSize.x, fboSize.y);
   glTextureParameteri(m_textures[G_TEXTURE_ALBEDO], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_ALBEDO], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //Normal
   glTextureStorage2D(m_textures[G_TEXTURE_NORMAL], 1, GL_RGBA32F, fboSize.x, fboSize.y);
   glTextureParameteri(m_textures[G_TEXTURE_NORMAL], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_NORMAL], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //Specular
   glTextureStorage2D(m_textures[G_TEXTURE_SPECULAR], 1, GL_RGBA32F, fboSize.x, fboSize.y);
   glTextureParameteri(m_textures[G_TEXTURE_SPECULAR], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_textures[G_TEXTURE_SPECULAR], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //Depth
   glTextureStorage2D(m_textures[G_TEXTURE_DEPTH], 1, GL_DEPTH_COMPONENT32F, fboSize.x, fboSize.y);

   //Attached textures
   const GLuint fbo = m_framebuffer.GetName();
   glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, m_textures[G_TEXTURE_ALBEDO], 0);
   glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT1, m_textures[G_TEXTURE_NORMAL], 0);
   glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT2, m_textures[G_TEXTURE_SPECULAR], 0);
   glNamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, m_textures[G_TEXTURE_DEPTH], 0);

   m_framebuffer.Validate();
}

void GBuffer::Destroy()
{
   glDeleteTextures(G_TEXTURE_COUNT, &m_textures[0]);
}

void GBuffer::Resize(const glm::ivec2& size)
{
   m_framebuffer.Resize(size);

   Destroy();
   Initialize();
}

void GBuffer::Clear()
{
   static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,  GL_COLOR_ATTACHMENT2 };
   static const int drawBuffersCount = 3;
   static GLfloat null[] = { -1, -1, -1, -1 };
   static GLfloat ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };

   const GLuint fbo = m_framebuffer.GetName();
   glNamedFramebufferDrawBuffers(fbo, drawBuffersCount, drawBuffers);

   glClearNamedFramebufferfv(fbo, GL_COLOR, 0, null);
   glClearNamedFramebufferfv(fbo, GL_COLOR, 1, null);
   glClearNamedFramebufferfv(fbo, GL_COLOR, 2, null);
   glClearNamedFramebufferfv(fbo, GL_DEPTH, 0, ones);
}

void GBuffer::Bind()
{
   m_framebuffer.Bind();
}

GLuint GBuffer::GetAlbedoTexture() const
{
   return m_textures[G_TEXTURE_ALBEDO];
}

GLuint GBuffer::GetNormalTexture() const
{
   return m_textures[G_TEXTURE_NORMAL];
}

GLuint GBuffer::GetSpecularTexture() const
{
   return m_textures[G_TEXTURE_SPECULAR];
}

GLuint GBuffer::GetDepthTexture() const
{
   return m_textures[G_TEXTURE_DEPTH];
}
