#pragma once
#include <vector>
#include "Scene/Terrain/Node.h"

namespace Prospect
{
   class QuadTree
   {
   public:
      QuadTree(
         const glm::vec3& origin,
         const float size);

      void Update(const glm::vec3& position);
      const std::vector<Node*>& GetEndNodes() const;

   private:
      int FindClosestEndNodeIndex(const glm::vec3& position) const;
      bool NewClosestEndNode(const glm::vec3& position);
      void ForceUpdate(const glm::vec3& position);

      Node m_rootNode;
      std::vector<Node*> m_endNodes;
      int m_closestEndNodeIndex;
   };
}
