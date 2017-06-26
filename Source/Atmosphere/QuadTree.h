#pragma once
#include <GL/glew.h>
#include <vector>
#include <stack>
#include "Node.h"

#include <iostream>


class QuadTree
{
public:
   QuadTree(
      const glm::vec3& origin,
      const float size,
      const GLint originLocation,
      const GLint sizeLocation,
      const GLint levelLocation,
      const GLint edgeScalingLocation);

   void Update(const glm::vec3& camera);
   void Draw();

private:
   Node m_rootNode;
   std::vector<Node*> m_endNodes;

   const GLint m_originLocation;
   const GLint m_sizeLocation;
   const GLint m_levelLocation;
   const GLint m_edgeScalingLocation;

};