#include "ProspectEngine_pch.h"

#include "Atmosphere_impl.h"

using namespace Prospect;

Atmosphere_impl::Atmosphere_impl(Atmosphere& parent)
   :
   m_parent(parent),
   m_renderable(nullptr),
   m_isDirty(true),
   m_altitude(1500.1f),
   m_lightSource(nullptr)
{
}

Atmosphere_impl::~Atmosphere_impl()
{
}

void Atmosphere_impl::SetAltitude(const float altitude)
{
   m_altitude = altitude;
}

float Atmosphere_impl::GetAltitude() const
{
   return m_altitude;
}

void Atmosphere_impl::SetLightSource(const Light& lightSource)
{
   m_lightSource = &lightSource;
}

const Light* Atmosphere_impl::GetLightSource() const
{
   return m_lightSource;
}