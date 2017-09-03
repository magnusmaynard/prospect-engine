#pragma once
#include "Include/Entity.h"

#include <memory>
#include "Include/Mesh.h"
#include "Include/Material.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Defaults.h"

namespace Prospect
{
   class Entity_impl
   {
   public:
      Entity_impl(Entity& parent, unsigned long id);
      //Entity_impl(const Entity_impl& entity) = delete;
      //Entity_impl& operator=(const Entity_impl& entity) = delete;
      //Entity_impl(Entity_impl&& entity) = default;
      //Entity_impl& operator=(Entity_impl&& entity) = default;

      void SetMesh(const Mesh& mesh);
      Mesh& GetMesh();

      void SetMaterial(const Material& material);
      Material& GetMaterial();

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      glm::mat4 GetTransform() const;

   private:
      Entity& m_parent;

      Mesh m_mesh;
      Material m_material = DEFAULT_MATERIAL;
      unsigned long m_id = DEFAULT_ENTITY_ID;

      glm::vec3 m_translation;
   };
}
