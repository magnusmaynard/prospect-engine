#include "ProspectEngine_pch.h"
#include "Include/Lights/Light.h"
#include "EngineDefines.h"

using namespace Prospect;

Light::Light(
   const glm::vec3& position,
   const glm::vec3& direction)
   :
   m_position(position),
   m_direction(direction),
   m_brightness(DEFAULT_LIGHT_BRIGHTNESS),
   m_color(DEFAULT_LIGHT_COLOR)
{
}

void Light::SetPosition(const glm::vec3& position)
{
   m_position = position;
}

glm::vec3 Light::GetPosition() const
{
   return m_position;
}

void Light::SetDirection(const glm::vec3& direction)
{
   m_direction = direction;
}

glm::vec3 Light::GetDirection() const
{
   return m_direction;
}

void Light::SetBrightness(const float brightness)
{
   m_brightness = brightness;
}

float Light::GetBrightness() const
{
   return m_brightness;
}

void Light::SetColor(const Color& color)
{
   m_color = color;
}

Color Light::GetColor() const
{
   return m_color;
}
