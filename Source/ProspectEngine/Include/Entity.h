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
      Entity(Mesh& mesh, Material& material);
      Entity(std::shared_ptr<Entity_impl>& impl);

      ~Entity();
      Entity(const Entity& entity) = delete;
      Entity& operator=(const Entity& entity) = delete;
      Entity(Entity&& entity);
      Entity& operator=(Entity&& entity);

      void SetMesh(Mesh& mesh);
      void SetMaterial(Material& material);

      std::optional<Mesh> GetMesh();
      std::optional<const Mesh> GetMesh() const;

      std::optional<Material> GetMaterial();
      std::optional<const Material> GetMaterial() const;

      void SetTranslation(const glm::vec3& translation);
      glm::vec3 GetTranslation() const;
      void SetRotation(const glm::vec3& rotation);
      glm::vec3 GetRotation() const;
      void SetScale(const glm::vec3& scale);
      glm::vec3 GetScale() const;

      void AddEntity(Entity& entity);
      Entity GetEntity(unsigned int index);
      int GetEntityCount() const;

   private:
      std::shared_ptr<Entity_impl> m_impl;

      friend class Renderer;
      friend class Scene_impl;
      friend class Entity_impl;
      friend class EntityLibrary;
   };
}
