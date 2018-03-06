#include "ProspectEngine_pch.h"

#include "LightingPass.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/ShadowMaps.h"

using namespace Prospect;
using namespace glm;

LightingPass::LightingPass(
   ShaderLibrary& shaderLibrary,
   const GBuffer& gbuffer,
   const ShadowMaps& shadowMaps)
   :
   m_shader(shaderLibrary.GetLightingShader()),
   m_gBuffer(gbuffer),
   m_shadowMaps(shadowMaps)
{
}

void LightingPass::Render()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glBlendFunc(GL_ONE, GL_ZERO);

   glDrawBuffer(GL_BACK);
   glBindTextureUnit(0, m_gBuffer.GetAlbedoTexture());
   glBindTextureUnit(1, m_gBuffer.GetNormalTexture());
   glBindTextureUnit(2, m_gBuffer.GetSpecularTexture());
   glBindTextureUnit(3, m_gBuffer.GetDepthTexture());
   glBindTextureUnit(4, m_shadowMaps.GetTexture());

   m_shader.Bind();
   m_shader.Update(m_shadowMaps);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
