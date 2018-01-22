#include "ProspectEngine_pch.h"

#include "Scene/Lights/Light_impl.h"

#include "Include/Lights/Light.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

Light::Light(
   const glm::vec3& position,
   const glm::vec3& direction,
   const LightType& type)
   :
   m_impl(std::make_shared<Light_impl>(position, direction, type))
{
}

Light::Light(std::shared_ptr<Light_impl>& impl)
   :
   m_impl(impl)
{
}

void Light::SetPosition(const glm::vec3& value)
{
   m_impl->SetPosition(value);
}

glm::vec3 Light::GetPosition() const
{
   return m_impl->GetPosition();
}

void Light::SetDirection(const glm::vec3& value)
{
   m_impl->SetDirection(value);
}

glm::vec3 Light::GetDirection() const
{
   return m_impl->GetDirection();
}

void Light::SetColor(const Color& value)
{
   m_impl->SetColor(value);
}

Color Light::GetColor() const
{
   return m_impl->GetColor();
}

void Light::SetBrightness(const float value)
{
   m_impl->SetBrightness(value);
}

float Light::GetBrightness() const
{
   return m_impl->GetBrightness();
}

void Light::SetRange(const float value)
{
   m_impl->SetRange(value);
}

float Light::GetRange() const
{
   return m_impl->GetRange();
}

void Light::SetAngle(const float value)
{
   m_impl->SetAngle(value);
}

float Light::GetAngle() const
{
   return m_impl->GetAngle();
}

void Light::SetType(const LightType& value)
{
   m_impl->SetType(value);
}
LightType Light::GetType() const
{
   return m_impl->GetType();
}
