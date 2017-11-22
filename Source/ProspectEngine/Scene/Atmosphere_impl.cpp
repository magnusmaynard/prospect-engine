#include "ProspectEngine_pch.h"

#include "Atmosphere_impl.h"

#include "Engine/EngineDefines.h"
#include "Renderer/Renderables/IRenderable.h"

using namespace Prospect;
using namespace glm;

Atmosphere_impl::Atmosphere_impl()
   :
   m_renderable(nullptr),
   m_light(vec3(), DEFAULT_ATMOSPHERE_LIGHT_DIRECTION),
   m_altitude(DEFAULT_ATMOSPHERE_ALTITUDE),
   m_innerRadius(DEFAULT_ATMOSPHERE_INNER_RADIUS),
   m_outterRadius(DEFAULT_ATMOSPHERE_OUTTER_RADIUS),
   m_densityScale(DEFAULT_ATMOSPHERE_DENSITY_SCALE)
{
}

Atmosphere_impl::~Atmosphere_impl()
{
}

void Atmosphere_impl::SetSunDirection(const vec3& value)
{
   m_light.SetDirection(value);
   MakeDirty();
}

vec3 Atmosphere_impl::GetSunDirection() const
{
   return m_light.GetDirection();
}

void Atmosphere_impl::SetInnerRadius(const float value)
{
   m_innerRadius = value;
   MakeDirty();
}

float Atmosphere_impl::GetInnerRadius() const
{
   return m_innerRadius;
}

void Atmosphere_impl::SetOutterRadius(const float value)
{
   m_outterRadius = value;
   MakeDirty();
}

float Atmosphere_impl::GetOutterRadius() const
{
   return m_outterRadius;
}

void Atmosphere_impl::SetAltitude(const float altitude)
{
   m_altitude = altitude;
   MakeDirty();
}

float Atmosphere_impl::GetAltitude() const
{
   return m_altitude;
}

void Atmosphere_impl::SetDensityScale(const float value)
{
   m_densityScale = value;
   MakeDirty();
}

float Atmosphere_impl::GetDensityScale() const
{
   return m_densityScale;
}

void Atmosphere_impl::SetRenderable(IRenderable* value) const
{
   m_renderable = value;
}

Light_impl& Atmosphere_impl::GetLightImpl()
{
   return m_light;
}

const Light_impl& Atmosphere_impl::GetLightImpl() const
{
   return m_light;
}

void Atmosphere_impl::MakeDirty() const
{
   if(m_renderable)
   {
      m_renderable->MakeDirty();
   }
}
