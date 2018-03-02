#include "ProspectEngine_pch.h"

#include "ShadowMap.h"

#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;
using namespace glm;

ShadowMap::ShadowMap(
   ShaderLibrary& shaderLibrary,
   const Light_impl& light)
   :
   m_light(light)
{
   glCreateFramebuffers(1, &m_shadowFBO);
   glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

   glCreateTextures(GL_TEXTURE_2D, 1, &m_shadowTexture);
   glTextureStorage2D(m_shadowTexture, 1, GL_DEPTH_COMPONENT32F, TEXTURE_SIZE.x, TEXTURE_SIZE.y);
   
   //TODO: Does this make sense here, this is only for sampling?
   //glTextureParameteri(m_shadowTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //glTextureParameteri(m_shadowTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   //glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   //glTextureParameteri(m_shadowTexture, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

   glNamedFramebufferTexture(m_shadowFBO, GL_DEPTH_ATTACHMENT, m_shadowTexture, 0);
}

void ShadowMap::Render()
{
}

void ShadowMap::UpdateLightMVP()
{
   mat4 lightModel = translate(m_light.GetPosition());

   mat4 lightView = lookAt(
      m_light.GetPosition(),
      m_light.GetPosition() + m_light.GetDirection(),
      POS_Y);

   mat4 lightProjection = frustum(-1, 1, -1, 1, 1, 1000);

   m_lightMVP = lightProjection * lightView * lightModel;
}


