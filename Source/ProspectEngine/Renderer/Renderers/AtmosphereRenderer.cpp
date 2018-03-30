#include "ProspectEngine_pch.h"

#include "AtmosphereRenderer.h"

#include "Scene/Atmosphere_impl.h"
#include "Resources/Resources.h"
#include "Renderer/Textures/DepthTexture.h"
#include "Renderer/Pipeline/GBuffer.h"

using namespace Prospect;
using namespace glm;

AtmosphereRenderer::AtmosphereRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetAtmosphereShader())
{
}

AtmosphereRenderer::~AtmosphereRenderer()
{
}

AtmosphereRenderable& AtmosphereRenderer::GetRenderable(const Atmosphere_impl& atmosphere)
{
   auto itr = m_atmosphereRenderables.find(atmosphere.GetId());
   if (itr == m_atmosphereRenderables.end())
   {
      AtmosphereRenderable renderable;

      //TODO:

      return m_atmosphereRenderables.emplace(atmosphere.GetId(), renderable).first->second;
   }

   return itr->second;
}

void AtmosphereRenderer::Render(const Atmosphere_impl& atmosphere, const GBuffer& gBuffer)
{
   AtmosphereRenderable& renderable = GetRenderable(atmosphere);

   if (atmosphere.IsDirty())
   {
      m_shader.Update(atmosphere);
      atmosphere.Clean();
   }

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);

   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   glDrawBuffer(GL_BACK);
   glBindTextureUnit(3, gBuffer.GetDepthTexture());

   m_shader.Bind();

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
