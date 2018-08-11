#include "ProspectEngine_pch.h"

#include "Scene/Material_impl.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

Material_impl::Material_impl(
   const unsigned id,
   const Color& diffuse,
   const Color& emissive,
   const Color& specular,
   const int specularPower,
   const bool isLit)
   :
   m_id(id),
   m_diffuse(diffuse),
   m_emissive(emissive),
   m_specular(specular),
   m_specularPower(specularPower),
   m_isLit(isLit)
{
}

unsigned Material_impl::GetID() const
{
   return m_id;
}

void Material_impl::SetDiffuse(const Color& value)
{
   m_diffuse = value;
}

const Color& Material_impl::GetDiffuse() const
{
   return m_diffuse;
}

void Material_impl::SetEmissive(const Color& value)
{
   m_emissive = value;
}

const Color& Material_impl::GetEmissive() const
{
   return m_emissive;
}

void Material_impl::SetSpecular(const Color& value)
{
   m_specular = value;
}

const Color& Material_impl::GetSpecular() const
{
   return m_specular;
}

void Material_impl::SetSpecularPower(const int value)
{
   m_specularPower = value;
}

int Material_impl::GetSpecularPower() const
{
   return m_specularPower;
}

void Material_impl::SetIsLit(const bool value)
{
   m_isLit = value;
}

bool Material_impl::GetIsLit() const
{
   return m_isLit;
}
