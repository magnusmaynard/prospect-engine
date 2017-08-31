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
      Mesh(
         const std::vector<glm::vec3>& points,
         const std::vector<int>& indices);

      Mesh(
         const std::vector<glm::vec3>& points,
         const std::vector<int>& indices,
         const std::vector<glm::vec3>& normals);

      static Mesh CreateBox(const glm::vec3& position, const glm::vec3& size);
      static Mesh CreatePlane(const glm::vec3& position, const glm::vec2& size);

   private:
      std::vector<glm::vec3> m_points;
      std::vector<int> m_indices;
      std::vector<glm::vec3> m_normals;
   };
}
