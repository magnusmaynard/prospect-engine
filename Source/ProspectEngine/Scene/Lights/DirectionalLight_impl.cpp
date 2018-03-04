#include "ProspectEngine_pch.h"

#include "Scene/Lights/DirectionalLight_impl.h"

#include "Engine/EngineDefines.h"

using namespace Prospect;

DirectionalLight_impl::DirectionalLight_impl(const glm::vec3& direction)
   :
   m_type(LightType::Directional),
   m_position(glm::vec3(0)),
   m_direction(direction),
   m_brightness(DEFAULT_LIGHT_BRIGHTNESS),
   m_color(DEFAULT_LIGHT_COLOR),
   m_castShadows(DEFAULT_LIGHT_CAST_SHADOWS),
   m_shadowMapId(INVALID_SHADOW_MAP_ID)
{
}

void DirectionalLight_impl::SetType(const LightType& value)
{
   m_type = value;
}

LightType DirectionalLight_impl::GetType() const
{
   return m_type;
}

void DirectionalLight_impl::SetCastShadows(const bool value)
{
   m_castShadows = value;
}

bool DirectionalLight_impl::GetCastShadows() const
{
   return m_castShadows;
}

void DirectionalLight_impl::SetShadowMapId(const int value)
{
   m_shadowMapId = value;
}

int DirectionalLight_impl::GetShadowMapId() const
{
   return m_shadowMapId;
}

void DirectionalLight_impl::SetPosition(const glm::vec3& value)
{
   m_position = value;
}

glm::vec3 DirectionalLight_impl::GetPosition() const
{
   return m_position;
}

void DirectionalLight_impl::SetDirection(const glm::vec3& value)
{
   m_direction = value;
}

glm::vec3 DirectionalLight_impl::GetDirection() const
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
