#pragma once
#include <vector>
#include "Node.h"
#include "QuadTreeUniformLocations.h"

namespace Prospect
{
   class QuadTree
   {
   public:
      QuadTree(
         const glm::vec3& origin,
         const glm::vec3& normal,
         const glm::vec3& left,
         const glm::vec3& top,
         const float planetRadius,
         const glm::vec3& planetOrigin,
         const QuadTreeUniformLocations& locations);

      void Update(const glm::vec3& cameraPosition, const glm::vec3& cameraDirection);
      void Draw();

      const glm::vec3& QuadTree::GetLeft() const
      {
         return m_left;
      }

      const glm::vec3& QuadTree::GetTop() const
      {
         return m_top;
      }

      float QuadTree::GetPlanetRadius() const
      {
         return m_planetRadius;
      }

      const glm::vec3& QuadTree::GetPlanetOrigin() const
      {
         return m_planetOrigin;
      }

   private:
      Node m_rootNode;
      std::vector<Node*> m_endNodes;

      const glm::vec3 m_normal;
      const glm::vec3 m_left;
      const glm::vec3 m_top;
      const float m_planetRadius;
      const glm::vec3 m_planetOrigin;

      const QuadTreeUniformLocations m_locations;

   };
}