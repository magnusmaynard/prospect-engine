#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <array>

class QuadTree;

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
      const glm::vec3& normal,
      const glm::vec3& left,
      const glm::vec3& top,
      const float size);

   //TODO:Make update function non recursive.
   void Update(const glm::vec3& cameraPosition, const glm::vec3& camerDirection, std::vector<Node*>& endNodes);

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
   glm::vec3 m_origin; //TODO: These are the same as QuadTree, use those instead of storing them locally.
   glm::vec3 m_normal;
   glm::vec3 m_left;
   glm::vec3 m_top;
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
