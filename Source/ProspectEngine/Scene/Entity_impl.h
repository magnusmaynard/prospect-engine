#pragma once
#include "Include/Entity.h"

#include <deque>
#include "Include/Mesh.h"
#include "Include/Material.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "EngineDefines.h"
#include "Libraries/EntityLibrary.h"

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

      void SetMaterial(Material& material);
      Material* GetMaterial();

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      const glm::vec3& GetTranslation() const;

      void SetRotation(const glm::vec3& rotation);
      const glm::vec3& GetRotation() const;

      void SetScale(const glm::vec3& scale);
      const glm::vec3& GetScale() const;

      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntityAtIndex(unsigned int index);

      //Internal
      Entity_impl(
         Entity& parent,
         EntityLibrary& entityLib,
         unsigned int id,
         Entity* parentNode,
         Mesh* mesh,
         Material* material);
      
      void UpdateTransform(const glm::mat4& transform, const bool isParentDirty);
      glm::mat4& GetTransform();

      Mesh_impl* GetMeshImpl();

      IRenderable* GetRenderable();
      void SetRenderable(IRenderable* renderable);

   private:
      void UpdateLocalTransform();

      Entity& m_parent;
      EntityLibrary& m_entityLib;

      unsigned long m_id;
      Mesh* m_mesh;
      Material* m_material;

      Entity* m_parentNode;
      std::deque<Entity*> m_childNodes;

      glm::vec3 m_translation = DEFAULT_TRANSLATION;
      glm::vec3 m_rotation = DEFAULT_ROTATION;
      glm::vec3 m_scale = DEFAULT_SCALE;

      mutable bool m_isTransformDirty = true;
      glm::mat4 m_localTransform;
      glm::mat4 m_transform;

      IRenderable* m_renderable;
   };
}
