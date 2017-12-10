#include "ProspectEngine_pch.h"

#include "Node.h"

#include "Scene/Terrain/QuadTree.h"

using namespace Prospect;

Node::Node(
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

void Node::Update(const glm::vec3& cameraPosition, std::vector<Node*>& endNodes)
{
   glm::vec3 normal = glm::vec3(0, 1, 0);

   if (RequiresDivide(cameraPosition))
   {
      Divide();

      for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
      {
         m_children[i]->Update(cameraPosition, endNodes);
      }
   }
   else
   {
      //Node is out of range.
      m_isParent = false;
      m_edgeScalingIsDirty = true;

      //Update the closest end Node to the camera.
      endNodes.push_back(this);
   }
}

void Node::Divide()
{
   m_isParent = true;

   const float childSize = m_size * 0.5f;
   const float childSizeHalf = childSize * 0.5f;
   const int childLevel = m_level + 1;

   const glm::vec3 childOrigins[NUMBER_OF_CHILDREN] =
   {
      m_origin + glm::vec3(+childSizeHalf, 0, +childSizeHalf),
      m_origin + glm::vec3(-childSizeHalf, 0, +childSizeHalf),
      m_origin + glm::vec3(+childSizeHalf, 0, -childSizeHalf),
      m_origin + glm::vec3(-childSizeHalf, 0, -childSizeHalf)
   };

   for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
   {
      m_children[i] = std::make_unique<Node>(
         this,
         i,
         childLevel,
         childOrigins[i],
         childSize);
   }
}

void Node::UpdateEdgeScaling()
{
   if (m_edgeScalingIsDirty)
   {
      for (int i = 0; i < NUMBER_OF_EDGES; i++)
      {
         int scale = 1;
         Node* neighbour = FindNeighbour(static_cast<Direction>(i));

         //If the neighbouring node at the same level has children,
         //it means it is a higher level and the edge scale should be increase.
         if (neighbour != nullptr && neighbour->m_isParent)
         {
            scale = 2;
         }

         m_edgeScaling[i] = scale;
      }

      m_edgeScalingIsDirty = false;
   }
}

bool Node::IsLODInvalid(const glm::vec3& position) const
{
   return RequiresDivide(position) || RequiresMerge(position);
}

float Node::DistanceTo(const glm::vec3 position) const
{
   return length(m_origin - position);
}

bool Node::RequiresDivide(const glm::vec3& position) const
{
   const float distance = length(m_origin - position);

   return m_level < MAX_LEVEL && distance < m_size * DIVISION_THRESHOLD;
}

bool Node::RequiresMerge(const glm::vec3& position) const
{
   const float distance = length(m_origin - position);

   return m_level > 0 && distance > m_size * 2.0 * DIVISION_THRESHOLD;
}

Node* Node::FindNeighbour(const Direction& direction)
{
   Node* node = this;
   bool foundCommonNode = false;
   int currentIndex = 0;
   int indices[NUMBER_OF_LEVELS];

   //Look for nearest common parent between current node and neighbour.
   while (foundCommonNode == false)
   {
      //Go up tree
      //TODO: refactor using bit switching
      int newIndex = -1;

      switch (node->m_index)
      {
      case 0:
         switch (direction)
         {
         case Direction::Right:
            newIndex = 1;
            foundCommonNode = true;
            break;
         case Direction::Left:
            newIndex = 1;
            break;
         case Direction::Down:
            newIndex = 2;
            foundCommonNode = true;
            break;
         case Direction::Up:
            newIndex = 2;
            break;
         }
         break;
      case 1:
         switch (direction)
         {
         case Direction::Right:
            newIndex = 0;
            break;
         case Direction::Left:
            newIndex = 0;
            foundCommonNode = true;
            break;
         case Direction::Down:
            newIndex = 3;
            foundCommonNode = true;
            break;
         case Direction::Up:
            newIndex = 3;
            break;
         }
         break;
      case 2:
         switch (direction)
         {
         case Direction::Right:
            newIndex = 3;
            foundCommonNode = true;
            break;
         case Direction::Left:
            newIndex = 3;
            break;
         case Direction::Down:
            newIndex = 0;
            break;
         case Direction::Up:
            newIndex = 0;
            foundCommonNode = true;
            break;
         }
         break;
      case 3:
         switch (direction)
         {
         case Direction::Right:
            newIndex = 2;
            break;
         case Direction::Left:
            newIndex = 2;
            foundCommonNode = true;
            break;
         case Direction::Down:
            newIndex = 1;
            break;
         case Direction::Up:
            newIndex = 1;
            foundCommonNode = true;
            break;
         }
         break;
      }

      indices[currentIndex] = newIndex;
      currentIndex++;

      node = node->m_parent;

      //Edge node.
      if (node == nullptr)
      {
         return nullptr;
      }
   }

   //Go down indices from common parent to find child, which is the neigbour to the current node.
   Node* neighbour = node;
   while (neighbour->m_isParent && currentIndex > 0)
   {
      currentIndex--;

      auto index = indices[currentIndex];
      neighbour = neighbour->m_children[index].get();
   }

   return neighbour;
}
