#include "ProspectEngine_pch.h"

#include "Scene/Lights/Light_impl.h"

#include "Include/Lights/Light.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

Light::Light(
   const glm::vec3& position,
   const glm::vec3& direction)
   :
   m_impl(std::make_shared<Light_impl>(position, direction))
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
