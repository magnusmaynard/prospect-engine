#include "Include/Entity.h"

#include "Entity_impl.h"

using namespace Prospect;

Entity::Entity(unsigned long id)
   :
   m_impl(std::make_unique<Entity_impl>(*this, id))
{
}

//These must be declared in the cpp to allow for opaque unique pointers.
Entity::~Entity() = default;
Entity::Entity(Entity&& entity) = default;
Entity& Entity::operator=(Entity&& entity) = default;

void Entity::SetMesh(const Mesh& mesh)
{
   m_impl->SetMesh(mesh);
}

void Entity::SetMaterial(const Material& material)
{
   m_impl->SetMaterial(material);
}

Mesh& Entity::GetMesh()
{
   return m_impl->GetMesh();
}

Material& Entity::GetMaterial()
{
   return m_impl->GetMaterial();
}

void Entity::SetTranslation(const glm::vec3& translation)
{
   m_impl->SetTranslation(translation);
}

glm::mat4 Entity::GetTransform() const
{
   return m_impl->GetTransform();
}

Entity_impl& Entity::GetImpl()
{
   return *m_impl;
}
