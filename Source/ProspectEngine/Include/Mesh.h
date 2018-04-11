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
      Mesh(std::shared_ptr<Mesh_impl>& impl);

      void Clear();

      const std::vector<glm::vec3>& GetPositions() const;
      std::vector<glm::vec3>& GetPositions();
      const std::vector<unsigned int>& GetIndices() const;
      std::vector<unsigned int>& GetIndices();
      const std::vector<glm::vec3>& GetNormals() const;
      std::vector<glm::vec3>& GetNormals();

      unsigned long GetID() const;

   private:
      Mesh(unsigned long id);
      Mesh(
         unsigned long id,
         const std::vector<glm::vec3>& positions,
         const std::vector<unsigned int>& indices,
         const std::vector<glm::vec3>& normals);

      std::shared_ptr<Mesh_impl> m_impl;

      friend class Entity_impl;
      friend class MeshLibrary_impl;
   };
}
