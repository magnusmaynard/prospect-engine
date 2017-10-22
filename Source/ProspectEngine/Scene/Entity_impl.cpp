#include "ProspectEngine_pch.h"

#include "Scene/Entity_impl.h"

#include "EngineDefines.h"
#include "Renderer/Renderables/IRenderable.h"

using namespace Prospect;
using namespace glm;

Entity_impl::Entity_impl(
   Entity& parent,
   EntityLibrary& entityLib,
   unsigned int id,
   Entity* parentNode,
   Mesh* mesh,
   Material* material)
   :
   m_parent(parent),
   m_entityLib(entityLib),
   m_id(id),
   m_parentNode(parentNode),
   m_mesh(mesh),
   m_material(material),
   m_renderable(nullptr)
{
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

Material* Entity_impl::GetMaterial()
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

Entity& Entity_impl::AddEntity(Mesh* mesh, Material* material)
{
   Entity& childNode = m_entityLib.AddEntity(&m_parent, mesh, material);

   m_childNodes.push_back(&childNode);

   return childNode;
}

void Entity_impl::UpdateTransform(const mat4& transform, const bool isParentDirty)
{
   bool childrenDirty = false;

   if (m_isTransformDirty || isParentDirty)
   {
      UpdateLocalTransform();

      m_transform = transform * m_localTransform;

      childrenDirty = true;
      m_isTransformDirty = false;
   }

   for (auto& child : m_childNodes)
   {
      child->m_impl->UpdateTransform(m_transform, childrenDirty);
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

Entity& Entity_impl::GetEntityAtIndex(unsigned int index)
{
   if(index < 0 || index >= static_cast<int>(m_childNodes.size()))
   {
      throw std::exception("No Entity at index.");
   }

   return *m_childNodes[index];
}

Mesh_impl* Entity_impl::GetMeshImpl()
{
   if(m_mesh == nullptr)
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