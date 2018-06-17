#include "ProspectEngine_pch.h"

#include "AtmosphereRenderer.h"

#include "Scene/Atmosphere_impl.h"
#include "Resources/Resources.h"
#include "Renderer/Textures/DepthTexture.h"
#include "Renderer/Pipeline/Framebuffers/GBuffer.h"

using namespace Prospect;
using namespace glm;

AtmosphereRenderer::AtmosphereRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetAtmosphereShader()),
   m_renderDataLibrary()
{
}

AtmosphereRenderer::~AtmosphereRenderer()
{
}

void AtmosphereRenderer::Render(const Atmosphere_impl& atmosphere, const GBuffer& gBuffer)
{
   auto& renderData = m_renderDataLibrary.GetRenderData(atmosphere.GetId());

   if(!renderData.Initialised)
   {
      renderData.Initialised = true;
   }

   if (atmosphere.IsDirty())
   {
      m_shader.Update(atmosphere);
      atmosphere.Clean();
   }

   glPolygonMode(GL_FRONT, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
   glEnable(GL_CULL_FACE);
   glEnable(GL_BLEND);


   m_shader.Bind();

   glBindTextureUnit(3, gBuffer.GetDepthTexture());

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
