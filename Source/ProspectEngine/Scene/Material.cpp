#include "Include/Material.h"
#include "EngineDefines.h"

using namespace Prospect;

Material::Material(unsigned long id)
   :
   m_id(id),
   m_diffuse(DEFAULT_COLOR)
{
}

Material::Material(unsigned long id, const Color& diffuse)
   :
   m_id(id),
   m_diffuse(diffuse)
{
}

const Color& Material::GetDiffuse() const
{
   return m_diffuse;
}

unsigned long Material::GetID() const
{
   return m_id;
}
