#include "Include/Material.h"

using namespace Prospect;

const Color Material::DEFAULT_COLOR = Color(1, 0, 0);

Material::Material()
   :
   m_diffuse(DEFAULT_COLOR),
   m_ambient(DEFAULT_COLOR)
{
}

Material::Material(const Color& color)
   :
   m_diffuse(color),
   m_ambient(color)
{
}

Material::Material(const Color& diffuse, const Color& ambient)
   :
   m_diffuse(diffuse),
   m_ambient(ambient)
{
}

const Color& Material::GetDiffuse() const
{
   return m_diffuse;
}

const Color& Material::GetAmbient() const
{
   return m_ambient;
}