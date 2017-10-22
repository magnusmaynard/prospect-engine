#include "ProspectEngine_pch.h"

#include "RenderableAtmosphere.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

using namespace Prospect;

RenderableAtmosphere::RenderableAtmosphere(const GlobalUniformBuffers& globalUniformBuffers)
   :
   m_shader(ShaderFactory::CreateShader(Resources::ATMOSPHERE_VERTEX_SHADER, Resources::ATMOSPHERE_FRAGMENT_SHADER)),
   m_eyePosition(glm::vec3(0, 1500.1, 0))
   //m_atmosphereUniformBuffer(m_shader, "AtmosphereUniforms")
{
   globalUniformBuffers.Camera.Bind(m_shader);
   globalUniformBuffers.DirectionalLight.Bind(m_shader);

   //m_atmosphereUniformBuffer.Bind(m_shader);

   //m_atmosphereUniformBuffer.Update(AtmosphereUniforms(
   //   m_eyePosition
   //));
}

RenderableAtmosphere::~RenderableAtmosphere()
{
}

void RenderableAtmosphere::Render()
{
   m_shader.Bind();

   glDrawArrays(GL_TRIANGLES, 0, 6);
}
