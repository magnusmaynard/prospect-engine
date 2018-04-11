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
      void Clear();

      const std::vector<glm::vec3>& GetPositions() const;
      std::vector<glm::vec3>& GetPositions();
      const std::vector<unsigned int>& GetIndices() const;
      std::vector<unsigned int>& GetIndices();
      const std::vector<glm::vec3>& GetNormals() const;
      std::vector<glm::vec3>& GetNormals();

      //Internal
      Mesh_impl(
         unsigned long id);

      Mesh_impl(
         unsigned long id,
         const std::vector<glm::vec3>& positions,
         const std::vector<unsigned int>& indices,
         const std::vector<glm::vec3>& normals);

      bool IsDirty() const;
      void SetIsDirty(bool value) const;

      unsigned long GetId() const;

   private:
      unsigned long m_id = 0;

      std::vector<glm::vec3> m_positions;
      std::vector<unsigned int> m_indices;
      std::vector<glm::vec3> m_normals;

      mutable bool m_isDirty = true;
   };
}
