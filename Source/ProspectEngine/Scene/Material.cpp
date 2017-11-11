#include "ProspectEngine_pch.h"

#include "Include/Material.h"
#include "Scene/Material_impl.h"

using namespace Prospect;

Material::Material(unsigned long id)
   :
   m_impl(std::make_shared<Material_impl>(id))
{
}

Material::Material(unsigned long id, const Color& diffuse)
   :
   m_impl(std::make_shared<Material_impl>(id, diffuse))
{
}

Material::Material(std::shared_ptr<Material_impl>& impl)
   :
   m_impl(impl)
{
}

Material::~Material() = default;

const Color& Material::GetDiffuse() const
{
   return m_impl->GetDiffuse();
}

unsigned long Material::GetID() const
{
   return m_impl->GetID();
}
