#include "ProspectEngine_pch.h"

#include "Include/Material.h"
#include "Scene/Material_impl.h"

using namespace Prospect;

Material::Material(unsigned long id)
   :
   m_impl(std::make_unique<Material_impl>(*this, id))
{
}

Material::Material(unsigned long id, const Color& diffuse)
   :
   m_impl(std::make_unique<Material_impl>(*this, id, diffuse))
{
}

Material::~Material() = default;
Material::Material(Material&& other) = default;
Material& Material::operator=(Material&& other) = default;

const Color& Material::GetDiffuse() const
{
   return m_impl->GetDiffuse();
}

unsigned long Material::GetID() const
{
   return m_impl->GetID();
}
