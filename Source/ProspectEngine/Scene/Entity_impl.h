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
      void SetMesh(const Mesh& mesh);
      Mesh* GetMesh();

      void SetMaterial(const Material& material);
      Material* GetMaterial();

      unsigned long GetID() const;

      void SetTranslation(const glm::vec3& translation);
      glm::mat4 GetTransform() const;

   private:
      Entity& m_parent;

      std::unique_ptr<Mesh> m_mesh;
      std::unique_ptr<Material> m_material;
      unsigned long m_id = DEFAULT_ENTITY_ID;

      glm::vec3 m_translation;
   };
}
