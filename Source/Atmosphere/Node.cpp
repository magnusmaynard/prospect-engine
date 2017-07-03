#pragma once
#include "Node.h"

Node::Node(
   Node* parent,
   const int index,
   const int level,
   const glm::vec3& origin,
   const glm::vec3& left,
   const glm::vec3& top,
   const float size)
   :
   m_parent(parent),
   m_index(index),
   m_level(level),
   m_origin(origin),
   m_left(left),
   m_top(top),
   m_size(size)
{
}

void Node::Update(const glm::vec3& camera, std::vector<Node*>& endNodes)
{
   float distance = glm::length(m_origin - camera);

   if (m_level < MAX_LEVEL &&
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
      m_isParent = false;
      m_edgeScalingRequiresUpdating = true;
      endNodes.push_back(this);
   }
}

void Node::Divide()
{
   m_isParent = true;

   const float childSize = m_size * 0.5f;
   const float childSizeHalf = childSize * 0.5f;
   const int childLevel = m_level + 1;


   //glm::vec3(childSizeHalf, 0, childSizeHalf),
   //   glm::vec3(-childSizeHalf, 0, -childSizeHalf),
   //   glm::vec3(childSizeHalf, 0, -childSizeHalf)

   glm::vec3 originOffsets[NUMBER_OF_CHILDREN] =
   {
      m_left * -childSizeHalf + m_top * childSizeHalf,
      m_left * childSizeHalf + m_top * childSizeHalf,
      m_left * -childSizeHalf + m_top * -childSizeHalf,
      m_left * childSizeHalf + m_top * -childSizeHalf,
   };

   for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
   {
      m_children[i] = std::make_unique<Node>(
         this,
         i,
         childLevel,
         m_origin + originOffsets[i],
         m_left,
         m_top,
         childSize);
   }
}

void Node::UpdateEdgeScaling()
{
   if (m_edgeScalingRequiresUpdating)
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

      m_edgeScalingRequiresUpdating = false;
   }
}

Node* Node::FindNeighbour(const Direction& direction)
{
   Node* node = this;
   bool foundCommonNode = false;
   int currentIndex = 0;
   int m_indices[NUMBER_OF_LEVELS];

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

      m_indices[currentIndex] = newIndex;
      currentIndex++;

      node = node->m_parent;

      //Edge node.
      if (node == nullptr)
      {
         return nullptr;
      }
   }

   //Go down m_indices from common parent to find child, which is the neigbour to the current node.
   Node* neighbour = node;
   while (neighbour->m_isParent && currentIndex > 0)
   {
      currentIndex--;

      auto index = m_indices[currentIndex];
      neighbour = neighbour->m_children[index].get();
   }

   return neighbour;
}
