#pragma once
#include "Include/Entity.h"

#include <deque>
#include "Include/Mesh.h"
#include "Include/Material.h"
#include "Engine/EngineDefines.h"

namespace Prospect
{
   class Mesh_impl;
   class IRenderable;

   class Entity_impl
   {
   public:
      //Public
      void SetMesh(Mesh& mesh);
      Mesh* GetMesh();
      const Mesh* GetMesh() const;

      void SetMaterial(Material& material);
      Material* GetMaterial();
      const Material* GetMaterial() const;

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      const glm::vec3& GetTranslation() const;

      void SetRotation(const glm::vec3& rotation);
      const glm::vec3& GetRotation() const;

      void SetScale(const glm::vec3& scale);
      const glm::vec3& GetScale() const;

      void Add(Entity& entity);
      Entity GetEntity(unsigned int index);

      //Internal
      Entity_impl();
      Entity_impl(Mesh& mesh, Material& material);

      void SetParent(Entity_impl& parent);
      std::vector<std::shared_ptr<Entity_impl>>& GetChildren();
      
      void UpdateTransform(const glm::mat4& transform, const bool isParentDirty);
      glm::mat4& GetTransform();

      Mesh_impl* GetMeshImpl();

      IRenderable* GetRenderable();
      void SetRenderable(IRenderable* renderable);

      bool ChildEntityAdded() const;
      void ResetChildEntityAdded();

   private:
      void MarkParentAsDirty(); //TODO: Better name.
      void UpdateLocalTransform();

      static unsigned long m_nextEntityID;
      unsigned long m_id;

      Mesh* m_mesh;
      Material* m_material;

      Entity_impl* m_parent;
      std::vector<std::shared_ptr<Entity_impl>> m_children;

      glm::vec3 m_translation = DEFAULT_TRANSLATION;
      glm::vec3 m_rotation = DEFAULT_ROTATION;
      glm::vec3 m_scale = DEFAULT_SCALE;

      mutable bool m_childEntityAdded = true;
      mutable bool m_isTransformDirty = true;
      glm::mat4 m_localTransform;
      glm::mat4 m_transform;

      IRenderable* m_renderable;
   };
}
