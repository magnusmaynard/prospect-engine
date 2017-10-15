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
         const float size,
         const QuadTreeUniformLocations& locations);

      void Update(const glm::vec3& cameraPosition, const glm::vec3& cameraDirection);
      void Draw();

   private:
      Node m_rootNode;
      std::vector<Node*> m_endNodes;

      const QuadTreeUniformLocations m_locations;

   };
}