#include "ProspectEngine_pch.h"

#include "Scene/Material_impl.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;

Material_impl::Material_impl(unsigned long id)
   :
   m_id(id),
   m_diffuse(DEFAULT_COLOR)
{
}

Material_impl::Material_impl(unsigned long id, const Color& diffuse)
   :
   m_id(id),
   m_diffuse(diffuse)
{
}

const Color& Material_impl::GetDiffuse() const
{
   return m_diffuse;
}

unsigned long Material_impl::GetID() const
{
   return m_id;
}
