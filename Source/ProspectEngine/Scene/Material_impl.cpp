#include "ProspectEngine_pch.h"

#include "Scene/Material_impl.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

Material_impl::Material_impl(
   unsigned long id,
   const Color& diffuse,
   const Color& ambient,
   const Color& specular,
   float specularPower)
   :
   m_id(id),
   m_diffuse(diffuse),
   m_ambient(ambient),
   m_specular(specular),
   m_specularPower(specularPower)
{
}

unsigned long Material_impl::GetID() const
{
   return m_id;
}

void Material_impl::SetDiffuse(const Color& diffuse)
{
   m_diffuse = diffuse;
}

const Color& Material_impl::GetDiffuse() const
{
   return m_diffuse;
}

void Material_impl::SetAmbient(const Color& ambient)
{
   m_ambient = ambient;
}

const Color& Material_impl::GetAmbient() const
{
   return m_ambient;
}

void Material_impl::SetSpecular(const Color& specular)
{
   m_specular = specular;
}

const Color& Material_impl::GetSpecular() const
{
   return m_specular;
}

void Material_impl::SetSpecularPower(float specularPower)
{
   m_specularPower = specularPower;
}

float Material_impl::GetSpecularPower() const
{
   return m_specularPower;
}
