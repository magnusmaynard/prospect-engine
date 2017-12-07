#include "ProspectEngine_pch.h"

#include "DepthTexture.h"

using namespace Prospect;

DepthTexture::DepthTexture()
   :
   m_size(1024, 1024)//TODO: Use defaults.
{
   CreateTexture();
}

DepthTexture::~DepthTexture()
{
   DeleteTexture();
}

void DepthTexture::CreateTexture()
{
   glCreateTextures(GL_TEXTURE_2D, 1, &m_depthTexture);
   glTextureParameteri(m_depthTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTextureParameteri(m_depthTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   //Mutable textures are not supported with DSA.
   //It appears only mutable textures work with CopyTex().
   glBindTexture(GL_TEXTURE_2D, m_depthTexture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
}

void DepthTexture::DeleteTexture()
{
   glDeleteTextures(1, &m_depthTexture);
}

void DepthTexture::Update() const
{
   glNamedFramebufferReadBuffer(0, GL_BACK);
   glCopyTextureSubImage2D(m_depthTexture, 0, 0, 0, 0, 0, m_size.x, m_size.y);
}

void DepthTexture::Bind(const int textureUnit) const
{
   glBindTextureUnit(textureUnit, m_depthTexture);
}

void DepthTexture::Resize(const glm::ivec2& size)
{
   m_size = size;

   DeleteTexture();
   CreateTexture();
}
