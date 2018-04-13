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
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glBlendFunc(GL_ONE, GL_ZERO);

   glDrawBuffer(GL_BACK);
   glBindTextureUnit(0, gbuffer.GetAlbedoTexture());
   glBindTextureUnit(1, gbuffer.GetNormalTexture());
   glBindTextureUnit(2, gbuffer.GetSpecularTexture());
   glBindTextureUnit(3, gbuffer.GetDepthTexture());
   glBindTextureUnit(4, shadowMaps.GetTexture());

   m_shader.Bind();
   m_shader.Update(shadowMaps);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
