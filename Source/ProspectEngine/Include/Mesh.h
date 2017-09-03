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

   class EXPORT_DLL Mesh
   {
   public:
      Mesh();

      Mesh(
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices);

      Mesh(
         const std::vector<glm::vec3>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<glm::vec3>& normals);

      std::vector<glm::vec3>& GetVertices();
      std::vector<unsigned int>& GetIndices();

      static Mesh CreatePlane(const glm::vec3& origin, const glm::vec2& size);

      bool IsDirty() const; //TODO: Make this hidden, using an impl?
      void SetIsDirty(bool value);

   private:
      std::vector<glm::vec3> m_vertices;
      std::vector<unsigned int> m_indices;
      std::vector<glm::vec3> m_normals;

      bool m_isDirty = true;
   };
}
