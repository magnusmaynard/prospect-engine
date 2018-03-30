#pragma once

#include "Include/Mesh.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Prospect
{
   class Mesh_impl
   {
   public:
      //Public
      const std::vector<glm::vec3>& GetVertices() const;
      std::vector<glm::vec3>& GetVertices();
      const std::vector<unsigned int>& GetIndices() const;
      std::vector<unsigned int>& GetIndices();
      const std::vector<glm::vec3>& GetNormals() const;
      std::vector<glm::vec3>& GetNormals();

      //Internal
      Mesh_impl(
         unsigned long id);

      Mesh_impl(
         unsigned long id,
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<glm::vec3>& normals);

      bool IsDirty() const;
      void SetIsDirty(bool value) const;

      unsigned long GetId() const;

   private:
      unsigned long m_id = 0;

      std::vector<glm::vec3> m_vertices;
      std::vector<unsigned int> m_indices;
      std::vector<glm::vec3> m_normals;

      mutable bool m_isDirty = true;
   };
}
