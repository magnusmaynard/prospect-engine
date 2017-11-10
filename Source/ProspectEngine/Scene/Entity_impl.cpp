#include "ProspectEngine_pch.h"

#include "Scene/Entity_impl.h"

#include "Engine/EngineDefines.h"
#include "Renderer/Renderables/IRenderable.h"

using namespace Prospect;
using namespace glm;

unsigned long Entity_impl::m_nextEntityID = 0;

Entity_impl::Entity_impl(Mesh& mesh, Material& material)
   :
   m_id(m_nextEntityID++),
   m_mesh(&mesh),
   m_material(&material),
   m_parent(nullptr),
   m_renderable(nullptr)
{
}


Entity_impl::Entity_impl()
   :
   m_id(m_nextEntityID++),
   m_mesh(nullptr),
   m_material(nullptr),
   m_parent(nullptr),
   m_renderable(nullptr)
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
   m_mesh = &mesh;
}

void Entity_impl::SetMaterial(Material& material)
{
   m_material = &material;
}

Mesh* Entity_impl::GetMesh()
{
   return m_mesh;
}

const Mesh* Entity_impl::GetMesh() const
{
   return m_mesh;
}

Material* Entity_impl::GetMaterial()
{
   return m_material;
}

const Material* Entity_impl::GetMaterial() const
{
   return m_material;
}

unsigned long Entity_impl::GetID() const
{
   return m_id;
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
   m_childEntityAdded = true;

   if (m_parent)
   {
      m_parent->MarkParentAsDirty();
   }
}

void Entity_impl::Add(Entity& entity)
{
   entity.m_impl->SetParent(*this);

   m_children.push_back(entity.m_impl);

   MarkParentAsDirty();
}

void Entity_impl::UpdateTransform(const mat4& transform, const bool isParentDirty)
{
   bool isChildTransformDirty = false;

   if (m_isTransformDirty || isParentDirty)
   {
      UpdateLocalTransform();

      m_transform = transform * m_localTransform;

      isChildTransformDirty = true;
      m_isTransformDirty = false;
   }

   for (auto& child : m_children)
   {
      child->UpdateTransform(m_transform, isChildTransformDirty);
   }
}

mat4& Entity_impl::GetTransform()
{
   return m_transform;
}

void Entity_impl::UpdateLocalTransform()
{
   m_localTransform = translate(mat4(), m_translation);

   m_localTransform = rotate(m_localTransform, radians(m_rotation.x), POS_X);
   m_localTransform = rotate(m_localTransform, radians(m_rotation.y), POS_Y);
   m_localTransform = rotate(m_localTransform, radians(m_rotation.z), POS_Z);

   m_localTransform = scale(m_localTransform, m_scale);
}

Entity Entity_impl::GetEntity(unsigned int index)
{
   if (index < 0 || index >= static_cast<int>(m_children.size()))
   {
      throw std::exception("No Entity at index.");
   }

   return Entity(m_children[index]);
}

Mesh_impl* Entity_impl::GetMeshImpl()
{
   if (m_mesh == nullptr)
   {
      return nullptr;
   }

   return m_mesh->m_impl.get();
}

IRenderable* Entity_impl::GetRenderable()
{
   return m_renderable;
}

void Entity_impl::SetRenderable(IRenderable* renderable)
{
   m_renderable = renderable;
}

bool Entity_impl::ChildEntityAdded() const
{
   return m_childEntityAdded;
}

void Entity_impl::ResetChildEntityAdded()
{
   m_childEntityAdded = false;
}
