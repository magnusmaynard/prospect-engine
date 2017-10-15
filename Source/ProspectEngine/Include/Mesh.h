#pragma once

#include <vector>
#include <memory>

namespace Prospect
{
   class Mesh_impl;

   class Mesh
   {
   public:
      ~Mesh();
      Mesh(const Mesh& other) = delete;
      Mesh& operator=(const Mesh& other) = delete;
      Mesh(Mesh&& other);
      Mesh& operator=(Mesh&& other);

      const std::vector<glm::vec3>& GetVertices() const;
      std::vector<glm::vec3>& GetVertices();
      const std::vector<unsigned int>& GetIndices() const;
      std::vector<unsigned int>& GetIndices();

      unsigned long GetID() const;

   private:
      Mesh(unsigned long id);
      Mesh(
         unsigned long id,
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices);

      std::unique_ptr<Mesh_impl> m_impl;

      friend class Entity_impl;
      friend class MeshLibrary_impl;
   };
}
