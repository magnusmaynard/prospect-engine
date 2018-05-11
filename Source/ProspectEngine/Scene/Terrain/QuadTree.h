#pragma once
#include <vector>
#include "Scene/Terrain/Node.h"
#include <future>

namespace Prospect
{
   class QuadTree
   {
   public:
      QuadTree(
         const glm::vec3& origin,
         const float size);

      const std::vector<Node*>& GetEndNodes() const;

      void ForceUpdate(const glm::vec3& position);
      bool RequiresUpdate(const glm::vec3& position);

   private:
      int FindClosestEndNodeIndex(const glm::vec3& position) const;
      bool UpdateClosestEndNode(const glm::vec3& position);

      Node m_rootNode;
      std::vector<Node*> m_endNodes;
      int m_closestEndNodeIndex;
   };
}
