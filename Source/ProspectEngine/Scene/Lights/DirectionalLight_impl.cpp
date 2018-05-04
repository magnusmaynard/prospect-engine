#include "ProspectEngine_pch.h"

#include "Scene/Lights/DirectionalLight_impl.h"

#include "Engine/EngineDefines.h"

using namespace Prospect;
using namespace glm;;

DirectionalLight_impl::DirectionalLight_impl(const vec3& direction)
   :
   m_type(LightType::Directional),
   m_position(vec3(0)),
   m_direction(direction),
   m_brightness(Defaults::LIGHT_BRIGHTNESS),
   m_color(Defaults::LIGHT_COLOR),
   m_castShadows(Defaults::LIGHT_CAST_SHADOWS),
   m_shadowMapIndex(Defines::INVALID_SHADOW_MAP_ID),
   m_shadowCascades(Defaults::LIGHT_SHADOW_CASCADES),
   m_isDirty(true)
{
}

void DirectionalLight_impl::SetType(const LightType& value)
{
   MakeDirty();
   m_type = value;
}

LightType DirectionalLight_impl::GetType() const
{
   return m_type;
}

void DirectionalLight_impl::SetCastShadows(const bool value)
{
   MakeDirty();
   m_castShadows = value;
}

bool DirectionalLight_impl::GetCastShadows() const
{
   return m_castShadows;
}

void DirectionalLight_impl::SetShadowCascades(const std::vector<float>& value)
{
      MakeDirty();
      m_shadowCascades = value;
}

const std::vector<float>& DirectionalLight_impl::GetShadowCascades() const
{
   return m_shadowCascades;
}

void DirectionalLight_impl::SetPosition(const vec3& value)
{
   MakeDirty();
   m_position = value;
}

vec3 DirectionalLight_impl::GetPosition() const
{
   return m_position;
}

void DirectionalLight_impl::SetDirection(const vec3& value)
{
   MakeDirty();
   m_direction = value;
}

vec3 DirectionalLight_impl::GetDirection() const
{
   return m_direction;
}

void DirectionalLight_impl::SetColor(const Color& value)
{
   m_color = value;
}

Color DirectionalLight_impl::GetColor() const
{
   return m_color;
}

void DirectionalLight_impl::SetBrightness(const float value)
{
   m_brightness = value;
}

float DirectionalLight_impl::GetBrightness() const
{
   return m_brightness;
}

void DirectionalLight_impl::SetShadowMapIndex(const int value)
{
   MakeDirty();
   m_shadowMapIndex = value;
}

int DirectionalLight_impl::GetShadowMapIndex() const
{
   return m_shadowMapIndex;
}

bool DirectionalLight_impl::GetIsDirty() const
{
   return m_isDirty;
}

void DirectionalLight_impl::SetIsDirty(const bool value)
{
   m_isDirty = value;
}

void DirectionalLight_impl::MakeDirty()
{
   m_isDirty = true;
}
