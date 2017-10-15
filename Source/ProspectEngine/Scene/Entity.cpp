#include "ProspectEngine_pch.h"

#include "Include/Entity.h"

#include "Entity_impl.h"

using namespace Prospect;

Entity::Entity(
   EntityLibrary& entityLib,
   unsigned int id,
   Entity* parent,
   Mesh* mesh,
   Material* material)
   :
   m_impl(std::make_unique<Entity_impl>(*this, entityLib, id, parent, mesh, material))
{
}

//These must be declared in the cpp to allow for opaque unique pointers.
Entity::~Entity() = default;
Entity::Entity(Entity&& entity) = default;
Entity& Entity::operator=(Entity&& entity) = default;

void Entity::SetMesh(Mesh& mesh)
{
   m_impl->SetMesh(mesh);
}

void Entity::SetMaterial(Material& material)
{
   m_impl->SetMaterial(material);
}

Mesh* Entity::GetMesh()
{
   return m_impl->GetMesh();
}

Material* Entity::GetMaterial()
{
   return m_impl->GetMaterial();
}

void Entity::SetTranslation(const glm::vec3& translation)
{
   m_impl->SetTranslation(translation);
}

glm::vec3 Entity::GetTranslation () const
{
   return m_impl->GetTranslation();
}

void Entity::SetRotation(const glm::vec3& rotation)
{
   m_impl->SetRotation(rotation);
}

glm::vec3 Entity::GetRotation() const
{
   return m_impl->GetRotation();
}

void Entity::SetScale(const glm::vec3& scale)
{
   m_impl->SetScale(scale);
}

glm::vec3 Entity::GetScale() const
{
   return m_impl->GetScale();
}

Entity& Entity::AddEntity(Mesh* mesh, Material* material)
{
   return m_impl->AddEntity(mesh, material);
}

Entity& Entity::GetEntity(unsigned int index)
{
   return m_impl->GetEntityAtIndex(index);
}