#include "ProspectEngine_pch.h"

#include "RenderableAtmosphere.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;

RenderableAtmosphere::RenderableAtmosphere(
   const GlobalUniformBuffers& globalUniformBuffers,
   const Atmosphere_impl& atmosphere)
   :
   m_atmosphereUniformBuffer("AtmosphereUniforms"),
   m_atmosphere(atmosphere),
   m_shader(ShaderFactory::CreateShader(
      Resources::ATMOSPHERE_VERTEX_SHADER,
      Resources::ATMOSPHERE_FRAGMENT_SHADER))
{
   globalUniformBuffers.Camera.Bind(m_shader);
   globalUniformBuffers.DirectionalLight.Bind(m_shader);
   m_atmosphereUniformBuffer.Bind(m_shader);

   m_atmosphereUniformBuffer.Update({
      m_atmosphere.GetAltitude()
   });
}

RenderableAtmosphere::~RenderableAtmosphere()
{
}

void RenderableAtmosphere::Render()
{
   m_shader.Bind();

   glDrawArrays(GL_TRIANGLES, 0, 6);
}
