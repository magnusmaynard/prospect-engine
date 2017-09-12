#pragma once
#include "Defines.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Prospect
{
   //TODO: Export mesh to remove warnings, or use a lib instead of dll.
   //template class EXPORT_DLL std::vector<glm::vec3>;
   //template class EXPORT_DLL std::vector<int>;

   class Mesh
   {
   public:
      //TODO: make internal.
      Mesh(unsigned long id);
      Mesh(
         unsigned long id,
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices);

      EXPORT_DLL const std::vector<glm::vec3>& GetVertices() const;
      EXPORT_DLL std::vector<glm::vec3>& GetVertices();
      EXPORT_DLL const std::vector<unsigned int>& GetIndices() const;
      EXPORT_DLL std::vector<unsigned int>& GetIndices();

      //TODO: Make these hidden, using an impl.
      bool IsDirty() const;
      void SetIsDirty(bool value) const;

      unsigned long GetID() const;


   private:

      unsigned long m_id = 0;

      std::vector<glm::vec3> m_vertices;
      std::vector<unsigned int> m_indices;

      mutable bool m_isDirty = true;
   };
}
