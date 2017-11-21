#include "ProspectEngine_pch.h"

#include "Atmosphere_impl.h"

#include "Engine/EngineDefines.h"

using namespace Prospect;

Atmosphere_impl::Atmosphere_impl(Atmosphere& parent)
   :
   m_parent(parent),
   m_renderable(nullptr),
   m_isDirty(true),
   m_altitude(1500.1f),
   m_sunDirection(DEFAULT_ATMOSPHERE_SUN_DIRECTION),
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

const Light* Atmosphere_impl::GetLightSource() const //TODO: return impl
{
   return m_lightSource;
}

void Atmosphere_impl::SetSunDirection(const glm::vec3& value)
{
   m_sunDirection = value;
}

glm::vec3 Atmosphere_impl::GetSunDirection() const
{
   return m_sunDirection;
}
