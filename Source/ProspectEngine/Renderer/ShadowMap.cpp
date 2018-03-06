#include "ProspectEngine_pch.h"

#include "ShadowMap.h"

#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;
using namespace glm;

ShadowMap::ShadowMap()
{
}

void ShadowMap::Update(const DirectionalLight_impl& light)
{
   m_viewMatrix = lookAt(
      light.GetPosition(),
      light.GetPosition() + light.GetDirection(),
      POS_Y);

   m_projectionMatrix = ortho(-100.f, 100.f, -100.f, 100.f, -1000.f, 1000.f);

   //Move [-1, 1] space to [0, 1] required for sampling textures.
   const mat4 biasMatrix(
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0
   );

   m_shadowMatrix = biasMatrix * GetProjectionMatrix() * GetViewMatrix();
}

mat4 ShadowMap::GetShadowMatrix() const
{
   return m_shadowMatrix;
}

mat4 ShadowMap::GetViewMatrix() const
{
   return m_viewMatrix;
}

mat4 ShadowMap::GetProjectionMatrix() const
{
   return m_projectionMatrix;
}
