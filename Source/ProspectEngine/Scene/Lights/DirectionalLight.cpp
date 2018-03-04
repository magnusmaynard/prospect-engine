#include "ProspectEngine_pch.h"

#include "Scene/Lights/DirectionalLight_impl.h"

#include "Include/Lights/DirectionalLight.h"
#include "Engine/EngineDefines.h"
#include "Include/Color.h"
#include "Include/Lights/LightType.h"

using namespace Prospect;

DirectionalLight::DirectionalLight(const glm::vec3& direction)
   :
   m_impl(std::make_shared<DirectionalLight_impl>(direction))
{
}

DirectionalLight::DirectionalLight(std::shared_ptr<DirectionalLight_impl>& impl)
   :
   m_impl(impl)
{
}

void DirectionalLight::SetType(const LightType& value)
{
   m_impl->SetType(value);
}

LightType DirectionalLight::GetType() const
{
   return m_impl->GetType();
}

void DirectionalLight::SetPosition(const glm::vec3& value)
{
   m_impl->SetPosition(value);
}

glm::vec3 DirectionalLight::GetPosition() const
{
   return m_impl->GetPosition();
}

void DirectionalLight::SetDirection(const glm::vec3& value)
{
   m_impl->SetDirection(value);
}

glm::vec3 DirectionalLight::GetDirection() const
{
   return m_impl->GetDirection();
}

void DirectionalLight::SetColor(const Color& value)
{
   m_impl->SetColor(value);
}

Color DirectionalLight::GetColor() const
{
   return m_impl->GetColor();
}

void DirectionalLight::SetBrightness(const float value)
{
   m_impl->SetBrightness(value);
}

float DirectionalLight::GetBrightness() const
{
   return m_impl->GetBrightness();
}
