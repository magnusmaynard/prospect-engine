#include "Entity_impl.h"

#include <glm/gtc/matrix_transform.inl>

using namespace Prospect;
using namespace glm;

Entity_impl::Entity_impl(Entity& parent, unsigned long id)
   :
   m_parent(parent),
   m_id(id)
{
}

void Entity_impl::SetMesh(const Mesh& mesh)
{
   m_mesh = std::make_unique<Mesh>(mesh);
}

void Entity_impl::SetMaterial(const Material& material)
{
   m_material = std::make_unique<Material>(material);
}

Mesh* Entity_impl::GetMesh()
{
   return m_mesh.get();
}

Material* Entity_impl::GetMaterial()
{
   return m_material.get();
}

unsigned long Entity_impl::GetID() const
{
   return m_id;
}

void Entity_impl::SetTranslation(const glm::vec3& translation)
{
   m_translation = translation;
}

mat4 Entity_impl::GetTransform() const
{
   //TODO: This just returns translation right now.
   return translate(mat4(), m_translation);
}