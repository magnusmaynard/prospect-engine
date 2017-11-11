#include "ProspectEngine_pch.h"

#include "Include/Atmosphere.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;

Atmosphere::Atmosphere()
   :
   m_impl(std::make_unique<Atmosphere_impl>(*this)) //TODO:
{
}

Atmosphere::Atmosphere(std::shared_ptr<Atmosphere_impl>& impl)
   :
   m_impl(impl)
{
}

Atmosphere::~Atmosphere() = default;

void Atmosphere::SetAltitude(const float height)
{
   m_impl->SetAltitude(height);
}

const Light* Atmosphere::GetLightSource() const
{
   return m_impl->GetLightSource();
}

float Atmosphere::GetAltitude() const
{
   return m_impl->GetAltitude();
}

void Atmosphere::SetLightSource(const Light & lightSource)
{
   m_impl->SetLightSource(lightSource);
}
