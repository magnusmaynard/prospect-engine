#include "ProspectEngine_pch.h"

#include "Scene/Entity_impl.h"
#include "Scene/Material_impl.h"

#include "Engine/EngineDefines.h"
#include "Engine/Extensions.h"

using namespace Prospect;
using namespace glm;

Entity_impl::Entity_impl(Mesh& mesh, Material& material)
   :
   m_mesh(mesh.m_impl),
   m_material(material.m_impl),
   m_parent(nullptr)
{
}

Entity_impl::Entity_impl()
   :
   m_mesh(nullptr),
   m_material(nullptr),
   m_parent(nullptr)
{
}

void Entity_impl::SetParent(Entity_impl& parent)
{
   m_parent = &parent;
}

std::vector<std::shared_ptr<Entity_impl>>& Entity_impl::GetChildren()
{
   return m_children;
}

void Entity_impl::SetMesh(Mesh& mesh)
{
   m_mesh = mesh.m_impl;
}

std::optional<Mesh> Entity_impl::GetMesh()
{
   return MakeOptionalImpl<Mesh>(m_mesh);
}

void Entity_impl::SetMaterial(Material& material)
{
   m_material = material.m_impl;
}

std::optional<Material> Entity_impl::GetMaterial()
{
   return MakeOptionalImpl<Material>(m_material);
}

void Entity_impl::SetTranslation(const vec3& translation)
{
   m_translation = translation;

   m_isTransformDirty = true;
}

const vec3& Entity_impl::GetTranslation() const
{
   return m_translation;
}

void Entity_impl::SetRotation(const vec3& rotation)
{
   m_rotation = rotation;

   m_isTransformDirty = true;
}

const vec3& Entity_impl::GetRotation() const
{
   return m_rotation;
}

void Entity_impl::SetScale(const vec3& scale)
{
   m_scale = scale;

   m_isTransformDirty = true;
}

const vec3& Entity_impl::GetScale() const
{
   return m_scale;
}

void Entity_impl::MarkParentAsDirty()
{
   if (m_parent)
   {
      m_parent->MarkParentAsDirty();
   }
}

void Entity_impl::AddEntity(Entity& entity)
{
   entity.m_impl->SetParent(*this);

   m_children.push_back(entity.m_impl);

   MarkParentAsDirty();
}

void Entity_impl::UpdateTransformMatrix(const mat4& transform, const bool isParentDirty)
{
   bool isChildTransformDirty = false;

   if (m_isTransformDirty || isParentDirty)
   {
      UpdateLocalTransform();

      m_transform = transform * m_localTransform;
      m_normal = transpose(inverse(mat3(m_transform)));

      isChildTransformDirty = true;
      m_isTransformDirty = false;
   }

   for (auto& child : m_children)
   {
      child->UpdateTransformMatrix(m_transform, isChildTransformDirty);
   }
}

mat4 Entity_impl::GetTransformMatrix() const
{
   return m_transform;
}

mat3 Entity_impl::GetNormalMatrix() const
{
   return m_normal;
}

void Entity_impl::UpdateLocalTransform()
{
   m_localTransform = translate(mat4(), m_translation);

   m_localTransform = rotate(m_localTransform, radians(m_rotation.x), Defines::POS_X);
   m_localTransform = rotate(m_localTransform, radians(m_rotation.y), Defines::POS_Y);
   m_localTransform = rotate(m_localTransform, radians(m_rotation.z), Defines::POS_Z);

   m_localTransform = scale(m_localTransform, m_scale);
}

Entity Entity_impl::GetEntity(const unsigned int index)
{
   if (index < 0 || index >= static_cast<int>(m_children.size()))
   {
      throw std::exception("No Entity at index.");
   }

   return Entity(m_children[index]);
}

int Entity_impl::GetEntityCount() const
{
   return static_cast<int>(m_children.size());
}

Mesh_impl* Entity_impl::GetMeshImpl()
{
   return m_mesh.get();
}

Material_impl* Entity_impl::GetMaterialImpl()
{
   return m_material.get();
}

int Entity_impl::GetMaterialID() const
{
   return m_material->GetID();
}
