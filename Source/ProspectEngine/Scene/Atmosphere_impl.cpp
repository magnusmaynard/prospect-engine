#include "ProspectEngine_pch.h"

#include "Atmosphere_impl.h"

#include "Engine/EngineDefines.h"
#include "Renderer/Renderables/IRenderable.h"

using namespace Prospect;
using namespace glm;

Atmosphere_impl::Atmosphere_impl()
   :
   m_renderable(nullptr),
   m_light(nullptr),
   m_sunDirection(DEFAULT_ATMOSPHERE_SUN_DIRECTION),
   m_altitude(DEFAULT_ATMOSPHERE_ALTITUDE),
   m_innerRadius(DEFAULT_ATMOSPHERE_INNER_RADIUS),
   m_outterRadius(DEFAULT_ATMOSPHERE_OUTTER_RADIUS),
   m_densityScale(DEFAULT_ATMOSPHERE_DENSITY_SCALE)
{
}

Atmosphere_impl::~Atmosphere_impl()
{
}

void Atmosphere_impl::SetLight(DirectionalLight& light)
{
   m_light = &light;

   UpdateLight();
}

DirectionalLight* Atmosphere_impl::GetLight()
{
   return m_light;
}

void Atmosphere_impl::SetSunDirection(const vec3& value)
{
   m_sunDirection = value;

   UpdateLight();

   MakeDirty();
}

vec3 Atmosphere_impl::GetSunDirection() const
{
   return m_sunDirection;
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

void Atmosphere_impl::UpdateLight()
{
   if (m_light)
   {
      m_light->SetDirection(m_sunDirection);

      const vec3 down(0, -1, 0);
      const vec3 bias(0, -0.2, 0); //Ensures some brightness when sun is on the horizon.

      const float brightness = max(dot(m_sunDirection + bias, down), 0.f);
      m_light->SetBrightness(brightness);
   }
}

void Atmosphere_impl::MakeDirty() const
{
   if(m_renderable)
   {
      m_renderable->MakeDirty();
   }
}
