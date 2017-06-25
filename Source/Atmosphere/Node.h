#include <GL/glew.h>
#include <vector>
#include <stack>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <set>

enum class Direction
{
   Left,
   Right,
   Up,
   Down,
};

class Node
{
public:
   Node(
      Node* parent,
      const int index,
      const int level,
      const glm::vec3& origin,
      const float size)
      :
      m_parent(parent),
      m_index(index),
      m_level(level),
      m_origin(origin),
      m_size(size)
   {
   }

   void Update(const glm::vec3& camera, std::vector<Node*>& endNodes)
   {
      float distance = glm::length(m_origin - camera);

      //if (abs(distance - lastUpdateDistance) > UPDATE_DISTANCE_TOLERANCE)
      //{
      if (m_level < MAX_LEVELS &&
         distance < m_size * 2.0)
      {
         Divide();

         for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
         {
            m_children[i]->Update(camera, endNodes);
         }
      }
      else
      {
         //Node is out of range.
         endNodes.push_back(this);
         m_isParent = false;
      }
      //}
   }


   void Divide()
   {
      m_isParent = true;

      float childSize = m_size * 0.5;
      float childSizeHalf = childSize * 0.5;
      float childLevel = m_level + 1;

      std::vector<glm::vec3> originOffsets =
      {
         glm::vec3(-childSizeHalf, 0, childSizeHalf),
         glm::vec3(childSizeHalf, 0, childSizeHalf),
         glm::vec3(-childSizeHalf, 0, -childSizeHalf),
         glm::vec3(childSizeHalf, 0, -childSizeHalf)
      };

      for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
      {
         m_children[i] = std::make_unique<Node>(
            this,
            i,
            childLevel,
            m_origin + originOffsets[i],
            childSize);
      }
   }

   const float UPDATE_DISTANCE_TOLERANCE = 1.0;
   static const int NUMBER_OF_EDGES = 4;
   static const int NUMBER_OF_CHILDREN = 4;

   Node* m_parent;
   int m_index;
   int m_level;

   bool m_isParent = false;
   std::unique_ptr<Node> m_children[NUMBER_OF_CHILDREN];
   int m_edgeScaling[NUMBER_OF_EDGES];

   glm::vec3 m_origin;
   float m_size;
   const int MAX_LEVELS = 6;

};