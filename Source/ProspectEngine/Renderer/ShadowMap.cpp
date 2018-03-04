#include "ProspectEngine_pch.h"

#include "ShadowMap.h"

#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;
using namespace glm;

ShadowMap::ShadowMap(const DirectionalLight_impl& light)
   :
   m_light(light),
   m_isDirty(true)
{
}

void ShadowMap::Initialise()
{
   glCreateFramebuffers(1, &m_shadowFBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   glCreateTextures(GL_TEXTURE_2D, 1, &m_shadowTexture);
   glTextureStorage2D(m_shadowTexture, 1, GL_DEPTH_COMPONENT32F, TEXTURE_SIZE.x, TEXTURE_SIZE.y);

   glTextureParameteri(m_shadowTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   //Required for shadow sampler.
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

   glNamedFramebufferTexture(m_shadowFBO, GL_DEPTH_ATTACHMENT, m_shadowTexture, 0);

   const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (error != GL_FRAMEBUFFER_COMPLETE)
   {
      std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   }
}

void ShadowMap::Clear()
{
   static GLfloat ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   glClearNamedFramebufferfv(m_shadowFBO, GL_DEPTH, 0, ones);
}

bool ShadowMap::GetIsDirty() const
{
   return m_isDirty;
}

void ShadowMap::SetIsDirty(const bool value) const
{
   m_isDirty = value;
}

mat4 ShadowMap::GetProjection() const
{
   UpdateProjectionAndView();

   return m_projection;
}

mat4 ShadowMap::GetView() const
{
   UpdateProjectionAndView();

   return m_view;
}

GLuint ShadowMap::GetShadowTexture() const
{
   return m_shadowTexture;
}

void ShadowMap::Bind()
{
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
   glViewport(0, 0, TEXTURE_SIZE.x, TEXTURE_SIZE.y);
}

void ShadowMap::UpdateProjectionAndView() const
{
   if (m_isDirty)
   {
      m_isDirty = false;

      m_view = lookAt(
         m_light.GetPosition(),
         m_light.GetPosition() + m_light.GetDirection(),
         POS_Y);

      m_projection = ortho(-100.f, 100.f, -100.f, 100.f, -1000.f, 1000.f);
   }
}

