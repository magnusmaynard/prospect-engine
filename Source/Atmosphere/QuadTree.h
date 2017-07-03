#pragma once
#include <vector>
#include "Node.h"
#include "QuadTreeUniformLocations.h"

class QuadTree
{
public:
   QuadTree(
      const glm::vec3& origin,
      const glm::vec3& normal,
      const glm::vec3& left,
      const glm::vec3& top,
      const float size,
      const QuadTreeUniformLocations& locations);

   void Update(const glm::vec3& camera);
   void Draw();

private:
   Node m_rootNode;
   std::vector<Node*> m_endNodes;

   const glm::vec3 m_normal;
   const glm::vec3 m_left;
   const glm::vec3 m_top;

   const QuadTreeUniformLocations m_locations;

};