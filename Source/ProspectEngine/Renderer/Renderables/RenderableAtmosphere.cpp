#include "ProspectEngine_pch.h"

#include "RenderableAtmosphere.h"

#include "Scene/Atmosphere_impl.h"
#include "Resources/Resources.h"
#include "Renderer/Textures/DepthTexture.h"

using namespace Prospect;
using namespace glm;

RenderableAtmosphere::RenderableAtmosphere(
   ShaderLibrary& shaderLibrary,
   const GBuffer& gBuffer,
   const Atmosphere_impl& atmosphere)
   :
   m_shader(shaderLibrary.GetAtmosphereShader()),
   m_gBuffer(gBuffer),
   m_atmosphere(atmosphere),
   m_isDirty(true)
{
}

RenderableAtmosphere::~RenderableAtmosphere()
{
}

void RenderableAtmosphere::UpdateUniformsIfDirty()
{
   if (m_isDirty)
   {
      m_isDirty = false;

      m_shader.Update(m_atmosphere);
   }
}

void RenderableAtmosphere::Render()
{
   UpdateUniformsIfDirty();


   //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
   
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   
   //glBlendFunc(GL_ONE, GL_ZERO);
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
   
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   
   glDrawBuffer(GL_BACK);
   glBindTextureUnit(3, m_gBuffer.GetDepthTexture());
   
   m_shader.Bind();
   
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RenderableAtmosphere::MakeDirty()
{
   m_isDirty = true;
}
