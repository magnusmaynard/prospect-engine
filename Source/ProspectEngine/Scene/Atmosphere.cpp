#include "ProspectEngine_pch.h"

#include "Include/Atmosphere.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;

Atmosphere::Atmosphere()
   :
   m_impl(std::make_unique<Atmosphere_impl>(*this))
{
}

Atmosphere::~Atmosphere() = default;

void Atmosphere::SetAltitude(float height)
{
   m_impl->SetAltitude(height);
}

float Atmosphere::GetAltitude() const
{
   return m_impl->GetAltitude();
}

void Atmosphere::SetLightSource(const Light & lightSource)
{
   m_impl->SetLightSource(lightSource);
}
