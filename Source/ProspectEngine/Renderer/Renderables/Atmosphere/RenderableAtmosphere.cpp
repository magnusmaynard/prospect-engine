#include "ProspectEngine_pch.h"

#include "RenderableAtmosphere.h"

#include "Scene/Atmosphere_impl.h"
#include "Resources/Resources.h"
#include "Renderer/Textures/DepthTexture.h"

using namespace Prospect;
using namespace glm;

RenderableAtmosphere::RenderableAtmosphere(
   ShaderLibrary& shaderLibrary,
   const DepthTexture& depthTexture,
   const Atmosphere_impl& atmosphere)
   :
   m_scattering(shaderLibrary, depthTexture),
   m_sun(shaderLibrary),
   //m_clouds(shaderLibrary)
   m_atmosphere(atmosphere),
   m_isDirty(true)
{
}

RenderableAtmosphere::~RenderableAtmosphere()
{
}

void RenderableAtmosphere::UpdateUniformsIfDirty()
{
   if (m_isDirty)
   {
      m_isDirty = false;

      m_sun.UpdateUniforms(m_atmosphere);
      m_scattering.UpdateUniforms(m_atmosphere);
      //m_clouds.UpdateUniforms(m_atmosphere);
   }
}

void RenderableAtmosphere::Render()
{
   UpdateUniformsIfDirty();

   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

   m_sun.Render();
   m_scattering.Render();
   //m_clouds.Render();
}

void RenderableAtmosphere::MakeDirty()
{
   m_isDirty = true;
}
