#pragma once
#include "Include/Entity.h"

#include <memory>
#include "Include/Mesh.h"
#include "Include/Material.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Defaults.h"
#include "RendererDefines.h"

namespace Prospect
{
   class Entity_impl
   {
   public:
      Entity_impl(Entity& parent, unsigned long id, Mesh& mesh, Material& material);

      void SetMesh(Mesh& mesh);
      Mesh& GetMesh();

      void SetMaterial(Material& material);
      Material& GetMaterial();

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      const glm::vec3& GetTranslation() const;

      void SetRotation(const glm::vec3& rotation);
      const glm::vec3& GetRotation() const;

      void SetScale(const glm::vec3& scale);
      const glm::vec3& GetScale() const;

      const glm::mat4& GetTransform() const;

   private:
      Entity& m_parent;

      Mesh& m_mesh;
      Material m_material; //TODO: make reference
      unsigned long m_id = DEFAULT_ENTITY_ID;

      glm::vec3 m_translation = DEFAULT_TRANSLATION;
      glm::vec3 m_rotation = DEFAULT_ROTATION;
      glm::vec3 m_scale = DEFAULT_SCALE;

      mutable bool m_transformIsDirty = true;
      mutable glm::mat4 m_transform;
   };
}
