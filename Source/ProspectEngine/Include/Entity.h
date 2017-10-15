#pragma once

namespace Prospect
{
   class Entity_impl;
   class Mesh;
   class Material;
   class EntityLibrary;

   class Entity
   {
   public:
      ~Entity();
      Entity(const Entity& entity) = delete;
      Entity& operator=(const Entity& entity) = delete;
      Entity(Entity&& entity);
      Entity& operator=(Entity&& entity);

      void SetMesh(Mesh& mesh);
      void SetMaterial(Material& material);

      Mesh* GetMesh();
      Material* GetMaterial();

      void SetTranslation(const glm::vec3& translation);
      glm::vec3 GetTranslation() const;
      void SetRotation(const glm::vec3& rotation);
      glm::vec3 GetRotation() const;
      void SetScale(const glm::vec3& scale);
      glm::vec3 GetScale() const;

      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntity(unsigned int index);

   private:
      Entity(
         EntityLibrary& entityLib,
         unsigned int id,
         Entity* parent,
         Mesh* mesh,
         Material* material);

      std::unique_ptr<Entity_impl> m_impl;

      friend class Renderer;
      friend class Scene_impl;
      friend class Entity_impl;
      friend class EntityLibrary;
   };
}
