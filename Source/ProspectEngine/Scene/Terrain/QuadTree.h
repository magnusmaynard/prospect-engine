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

      void Update(const glm::vec3& cameraPosition);
      const std::vector<Node*>& GetEndNodes() const;

   private:
      Node m_rootNode;
      std::vector<Node*> m_endNodes;

   };
}
