#include "ProspectEngine_pch.h"

#include "ShadowMap.h"

#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;
using namespace glm;

ShadowMap::ShadowMap()
{
}

void ShadowMap::Update(const Bounds& bounds, const vec3& position, const vec3& direction, const float farClipDepth)
{
   m_farClipDepth = farClipDepth;

   m_viewMatrix = lookAt(
      position,
      position + direction,
      Defines::POS_Y);

   //Move near plane backwards, so more objects fit in the projection.
   const float projectionNearMultiplier = 10.f;

   m_projectionMatrix = ortho(
      bounds.Min.x,
      bounds.Max.x,
      bounds.Min.y,
      bounds.Max.y,
      bounds.Min.z * projectionNearMultiplier,
      bounds.Max.z);

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

float ShadowMap::GetFarClipDepth() const
{
   return m_farClipDepth;
}
