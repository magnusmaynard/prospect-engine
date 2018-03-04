#include "ProspectEngine_pch.h"

#include "Include/Atmosphere.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;

Atmosphere::Atmosphere()
   :
   m_impl(std::make_unique<Atmosphere_impl>())
{
}

Atmosphere::Atmosphere(std::shared_ptr<Atmosphere_impl>& impl)
   :
   m_impl(impl)
{
}

Atmosphere::~Atmosphere() = default;

void Atmosphere::SetLight(DirectionalLight& light)
{
   m_impl->SetLight(light);
}

DirectionalLight Atmosphere::GetLight()
{
   return m_impl->GetLight();
}

void Atmosphere::SetSunDirection(const glm::vec3& value)
{
   m_impl->SetSunDirection(value);
}

glm::vec3 Atmosphere::GetSunDirection() const
{
   return m_impl->GetSunDirection();
}

void Atmosphere::SetInnerRadius(const float value)
{
   m_impl->SetInnerRadius(value);
}

float Atmosphere::GetInnerRadius() const
{
   return m_impl->GetInnerRadius();
}

void Atmosphere::SetOutterRadius(const float value)
{
   m_impl->SetOutterRadius(value);
}

float Atmosphere::GetOutterRadius() const
{
   return m_impl->GetOutterRadius();
}

void Atmosphere::SetAltitude(const float value)
{
   m_impl->SetAltitude(value);
}

float Atmosphere::GetAltitude() const
{
   return m_impl->GetAltitude();
}

void Atmosphere::SetDensityScale(const float value)
{
   m_impl->SetDensityScale(value);
}

float Atmosphere::GetDensityScale() const
{
   return m_impl->GetDensityScale();
}
