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
      std::optional<Mesh> GetMesh();

      void SetMaterial(Material& material);
      std::optional<Material> GetMaterial();

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      const glm::vec3& GetTranslation() const;

      void SetRotation(const glm::vec3& rotation);
      const glm::vec3& GetRotation() const;

      void SetScale(const glm::vec3& scale);
      const glm::vec3& GetScale() const;

      void AddEntity(Entity& entity);
      Entity GetEntity(unsigned int index);
      int GetEntityCount() const;

      //Internal
      Entity_impl();
      Entity_impl(Mesh& mesh, Material& material);

      void SetParent(Entity_impl& parent);
      std::vector<std::shared_ptr<Entity_impl>>& GetChildren();
      
      void UpdateTransformMatrix(const glm::mat4& transform, const bool isParentDirty);
      glm::mat4 GetTransformMatrix() const;

      glm::mat3 GetNormalMatrix() const;

      Mesh_impl* GetMeshImpl();
      Material_impl* GetMaterialImpl();

      int GetMaterialID() const;

      IRenderable* GetRenderable();
      void SetRenderable(IRenderable* renderable);

      bool ChildEntityAdded() const;
      void ResetChildEntityAdded();

   private:
      void MarkParentAsDirty(); //TODO: Better name.
      void UpdateLocalTransform();

      static unsigned long m_nextEntityID;
      unsigned long m_id;

      std::shared_ptr<Mesh_impl> m_mesh;
      std::shared_ptr<Material_impl> m_material;

      Entity_impl* m_parent;
      std::vector<std::shared_ptr<Entity_impl>> m_children;

      glm::vec3 m_translation = DEFAULT_TRANSLATION;
      glm::vec3 m_rotation = DEFAULT_ROTATION;
      glm::vec3 m_scale = DEFAULT_SCALE;

      mutable bool m_childEntityAdded = true;
      mutable bool m_isTransformDirty = true;
      glm::mat4 m_localTransform;
      glm::mat4 m_transform;
      glm::mat3 m_normal;

      IRenderable* m_renderable;
   };
}
