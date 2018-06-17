#include "ProspectEngine_pch.h"

#include "GodRaysRenderer.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/Framebuffers/GBuffer.h"
#include "Renderer/Pipeline/Framebuffers/DisplayBuffer.h"
#include "Renderer/Debugger/Debug.h"

using namespace Prospect;

GodRaysRenderer::GodRaysRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetGodRaysShader())
{
}

GodRaysRenderer::~GodRaysRenderer()
{
}

void GodRaysRenderer::Render(const GBuffer& gBuffer, const DisplayBuffer& displayBuffer, const glm::vec3& sunPosition)
{
   glPolygonMode(GL_FRONT, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_CULL_FACE);

   m_shader.Bind();

   m_shader.Update({ glm::vec4(sunPosition, 0) });

   glBindTextureUnit(0, displayBuffer.GetDisplayTexture());
   glBindTextureUnit(1, gBuffer.GetAlbedoTexture());
   glBindTextureUnit(2, gBuffer.GetDepthTexture());

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
