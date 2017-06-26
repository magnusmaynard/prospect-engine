#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <array>

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

   //TODO:Make update function non recursive.
   void Update(const glm::vec3& camera, std::vector<Node*>& endNodes);

   void UpdateEdgeScaling();

private:
   void Divide();

   //TODO: Remove current index from update, just use lod.
   Node* FindNeighbour(const Direction& direction);

   static const int NUMBER_OF_EDGES = 4;
   static const int NUMBER_OF_CHILDREN = 4;
   static const int MAX_LEVEL = 8;
   static const int NUMBER_OF_LEVELS = MAX_LEVEL + 1;

   Node* m_parent;
   int m_index;
   int m_level;
   glm::vec3 m_origin;
   float m_size;

   bool m_isParent = false;
   std::unique_ptr<Node> m_children[NUMBER_OF_CHILDREN];
   std::array<int, NUMBER_OF_EDGES> m_edgeScaling;
   bool m_edgeScalingRequiresUpdating = true;

public:
   int Level() const
   {
      return m_level;
   }

   glm::vec3 Origin() const
   {
      return m_origin;
   }

   float Size() const
   {
      return m_size;
   }

   const std::array<int, NUMBER_OF_EDGES>& Edges() const
   {
      return m_edgeScaling;
   }
};
