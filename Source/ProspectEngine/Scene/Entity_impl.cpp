#include "Entity_impl.h"

#include <glm/gtc/matrix_transform.inl>
#include "RendererDefines.h"

using namespace Prospect;
using namespace glm;

Entity_impl::Entity_impl(Entity& parent, unsigned long id, Mesh& mesh, Material& material)
   :
   m_parent(parent),
   m_id(id),
   m_mesh(mesh),
   m_material(material)
{
}

void Entity_impl::SetMesh(Mesh& mesh)
{
   m_mesh = mesh;
}

void Entity_impl::SetMaterial(Material& material)
{
   m_material = material;
}

Mesh& Entity_impl::GetMesh()
{
   return m_mesh;
}

Material& Entity_impl::GetMaterial()
{
   return m_material;
}

unsigned long Entity_impl::GetID() const
{
   return m_id;
}

void Entity_impl::SetTranslation(const glm::vec3& translation)
{
   m_translation = translation;

   m_transformIsDirty = true;
}

const glm::vec3& Entity_impl::GetTranslation() const
{
   return m_translation;
}

void Entity_impl::SetRotation(const glm::vec3& rotation)
{
   m_rotation = rotation;

   m_transformIsDirty = true;
}

const glm::vec3& Entity_impl::GetRotation() const
{
   return m_rotation;
}

void Entity_impl::SetScale(const glm::vec3& scale)
{
   m_scale = scale;

   m_transformIsDirty = true;
}

const glm::vec3& Entity_impl::GetScale() const
{
   return m_scale;
}

const mat4& Entity_impl::GetTransform() const
{
   if(m_transformIsDirty)
   {
      m_transformIsDirty = false;

      m_transform = translate(mat4(), m_translation);

      m_transform = rotate(m_transform, m_rotation.x, POS_X);
      m_transform = rotate(m_transform, m_rotation.y, POS_Y);
      m_transform = rotate(m_transform, m_rotation.z, POS_Z);

      m_transform = scale(m_transform, m_scale);
   }

   return m_transform;
}