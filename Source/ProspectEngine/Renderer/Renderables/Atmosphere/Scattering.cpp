#include "ProspectEngine_pch.h"

#include "Scattering.h"
#include "Resources/Resources.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Textures/DepthTexture.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

Scattering::Scattering(
   ShaderLibrary& shaderLibrary,
   const DepthTexture& depthTexture)
   :
   m_shader(shaderLibrary.GetScatteringShader()),
   m_depthTexture(depthTexture)
{
}

Scattering::~Scattering()
{
}

void Scattering::UpdateUniforms(const Atmosphere_impl& atmosphere)
{
   m_shader.Update(atmosphere);
}

void Scattering::Render()
{
   m_shader.Bind();

   m_depthTexture.Update();
   m_depthTexture.Bind(0);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
