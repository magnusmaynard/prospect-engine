#include "ProspectEngine_pch.h"

#include "Scattering.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

Scattering::Scattering(const GlobalUniformBuffers& globalUniformBuffers)
   :
   m_shader(ShaderFactory::CreateShader(
      Resources::SCATTERING_VERTEX_SHADER,
      Resources::SCATTERING_FRAGMENT_SHADER)),
   m_uniformBuffer("ScatteringUniforms")
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
   glDrawArrays(GL_TRIANGLES, 0, 6);
}
