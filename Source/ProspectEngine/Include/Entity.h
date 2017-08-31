#pragma once
#include "Defines.h"
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> //TODO: change this

namespace Prospect
{
   class Entity_impl;
   class Mesh;
   class Material;

   class Entity
   {
   public:
      EXPORT_DLL Entity(unsigned long id);
      EXPORT_DLL ~Entity();
      EXPORT_DLL Entity(const Entity& entity) = delete;
      EXPORT_DLL Entity(Entity&& entity) noexcept;

      EXPORT_DLL void SetMesh(const Mesh& mesh);
      EXPORT_DLL void SetMaterial(const Material& material);

      EXPORT_DLL Mesh* GetMesh();
      EXPORT_DLL Material* GetMaterial();

      EXPORT_DLL void SetTranslation(const glm::vec3& translation);
      EXPORT_DLL glm::mat4 GetTransform() const;

      Entity_impl& GetImpl();

   private:
      std::unique_ptr<Entity_impl> m_impl;
   };
}
