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
      EXPORT_DLL Entity(unsigned long id, Mesh& mesh, Material& material);
      EXPORT_DLL ~Entity();
      EXPORT_DLL Entity(const Entity& entity) = delete;
      EXPORT_DLL Entity& operator=(const Entity& entity) = delete;
      EXPORT_DLL Entity(Entity&& entity);
      EXPORT_DLL Entity& operator=(Entity&& entity);

      EXPORT_DLL void SetMesh(Mesh& mesh);
      EXPORT_DLL void SetMaterial(Material& material);

      EXPORT_DLL Mesh& GetMesh();
      EXPORT_DLL Material& GetMaterial();

      EXPORT_DLL void SetTranslation(const glm::vec3& translation);
      EXPORT_DLL glm::vec3 GetTranslation() const;
      EXPORT_DLL void SetRotation(const glm::vec3& rotation);
      EXPORT_DLL glm::vec3 GetRotation() const;
      EXPORT_DLL void SetScale(const glm::vec3& scale);
      EXPORT_DLL glm::vec3 GetScale() const;

      Entity_impl& GetImpl();

   private:
      std::unique_ptr<Entity_impl> m_impl;
   };
}
