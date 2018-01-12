#include "ProspectEngine_pch.h"

#include "LightingPass.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/GBuffer.h"

using namespace Prospect;

LightingPass::LightingPass(
   ShaderLibrary& shaderLibrary,
   const GBuffer& gbuffer)
   :
   m_shader(shaderLibrary.GetLightingShader()),
   m_gBuffer(gbuffer)
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

   m_shader.Bind();
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
