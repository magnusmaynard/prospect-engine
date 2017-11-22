#include "ProspectEngine_pch.h"

#include "RenderableScattering.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

RenderableScattering::RenderableScattering(const GlobalUniformBuffers& globalUniformBuffers)
   :
   m_isDirty(true),
   m_atmosphereShader(ShaderFactory::CreateShader(
      Resources::ATMOSPHERE_VERTEX_SHADER,
      Resources::ATMOSPHERE_FRAGMENT_SHADER)),
   m_atmosphereUniformBuffer("AtmosphereUniforms")
{
   globalUniformBuffers.Camera.Bind(m_atmosphereShader);
   m_atmosphereUniformBuffer.Bind(m_atmosphereShader);
}

RenderableScattering::~RenderableScattering()
{
}

void RenderableScattering::UpdateUniforms(const Atmosphere_impl& atmosphere)
{
   m_atmosphereUniformBuffer.Update(atmosphere);
}

void RenderableScattering::Render()
{
   m_atmosphereShader.Bind();
   glDrawArrays(GL_TRIANGLES, 0, 6);
}
