#include "ProspectEngine_pch.h"

#include "Scene/Lights/Light_impl.h"

#include "Engine/EngineDefines.h"

using namespace Prospect;

Light_impl::Light_impl(
   const glm::vec3& position,
   const glm::vec3& direction,
   const LightType& type)
   :
   m_position(position),
   m_direction(direction),
   m_range(DEFAULT_LIGHT_RANGE),
   m_angle(DEFAULT_LIGHT_ANGLE),
   m_type(type),
   m_brightness(DEFAULT_LIGHT_BRIGHTNESS),
   m_color(DEFAULT_LIGHT_COLOR)
{
}

void Light_impl::SetPosition(const glm::vec3& value)
{
   m_position = value;
}

glm::vec3 Light_impl::GetPosition() const
{
   return m_position;
}

void Light_impl::SetDirection(const glm::vec3& value)
{
   m_direction = value;
}

glm::vec3 Light_impl::GetDirection() const
{
   return m_direction;
}

void Light_impl::SetColor(const Color& value)
{
   m_color = value;
}

Color Light_impl::GetColor() const
{
   return m_color;
}

void Light_impl::SetBrightness(const float value)
{
   m_brightness = value;
}

float Light_impl::GetBrightness() const
{
   return m_brightness;
}

void Light_impl::SetRange(const float value)
{
   m_range = value;
}

float Light_impl::GetRange() const
{
   return m_range;
}

void Light_impl::SetAngle(const float value)
{
   m_angle = value;
}

float Light_impl::GetAngle() const
{
   return m_angle;
}

void Light_impl::SetType(const LightType& value)
{
   m_type = value;
}

LightType Light_impl::GetType() const
{
   return m_type;
}
