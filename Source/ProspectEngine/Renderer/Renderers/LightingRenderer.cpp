#include "ProspectEngine_pch.h"

#include "LightingRenderer.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/Shadows/ShadowMaps.h"

using namespace Prospect;
using namespace glm;

LightingRenderer::LightingRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetLightingShader())
{
}

void LightingRenderer::Render(const GBuffer& gbuffer, const ShadowMaps& shadowMaps)
{
   glDisable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glBlendFunc(GL_ONE, GL_ZERO);
   glPolygonMode(GL_FRONT, GL_FILL);
   glDrawBuffer(GL_BACK);
   glEnable(GL_CULL_FACE);

   glBindTextureUnit(0, gbuffer.GetAlbedoTexture());
   glBindTextureUnit(1, gbuffer.GetNormalTexture());
   glBindTextureUnit(2, gbuffer.GetSpecularTexture());
   glBindTextureUnit(3, gbuffer.GetDepthTexture());
   glBindTextureUnit(4, shadowMaps.GetTexture());

   m_shader.Bind();
   m_shader.Update(shadowMaps);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
