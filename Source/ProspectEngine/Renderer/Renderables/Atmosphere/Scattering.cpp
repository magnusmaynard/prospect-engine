#include "ProspectEngine_pch.h"

#include "Scattering.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Textures/DepthTexture.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

Scattering::Scattering(
   const GlobalUniformBuffers& globalUniformBuffers,
   const DepthTexture& depthTexture)
   :
   m_shader(ShaderFactory::CreateShader(
      Resources::SCATTERING_VERTEX_SHADER,
      Resources::SCATTERING_FRAGMENT_SHADER)),
   m_uniformBuffer("ScatteringUniforms"),
   m_depthTexture(depthTexture)
{
   globalUniformBuffers.Camera.Bind(m_shader);
   m_uniformBuffer.Bind(m_shader);
}

Scattering::~Scattering()
{
}

void Scattering::UpdateUniforms(const Atmosphere_impl& atmosphere)
{
   m_uniformBuffer.Update(atmosphere);
}

void Scattering::Render()
{
   m_shader.Bind();

   m_depthTexture.Update();
   m_depthTexture.Bind(0);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
