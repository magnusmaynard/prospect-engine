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
      const GLint levelDifferencesLocation)
      :
      m_rootNode(nullptr, 0, 0, origin, size),
      m_originLocation(originLocation),
      m_sizeLocation(sizeLocation),
      m_levelLocation(levelLocation),
      m_edgeScalingLocation(levelDifferencesLocation)
   {
   }

   void Update(const glm::vec3& camera)
   {
      m_endNodes.clear();
      m_rootNode.Update(camera, m_endNodes);
   }


   //TODO:
   //- Crashes when zooming to far forward?
   //- Make update function non recursive.
   //- Add gets to Node.
   //- Remove current index from update, just use lod

   void Draw(const glm::vec3& camera)
   {
      for(auto& node : m_endNodes)
      {
         //Update edge scaling for this node.
         for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
         {
            node->m_edgeScaling[i] = CalculateEdgeScaling(node, static_cast<Direction>(i));
         }

         //Draw this node.
         glUniform3fv(m_originLocation, 1, &node->m_origin[0]);
         glUniform1f(m_sizeLocation, node->m_size);
         glUniform1f(m_levelLocation, node->m_level);
         glUniform4iv(m_edgeScalingLocation, 1, &node->m_edgeScaling[0]);

         glPatchParameteri(GL_PATCH_VERTICES, 4);
         glDrawArrays(GL_PATCHES, 0, 4);
      }
   }

   int CalculateEdgeScaling(Node* node, const Direction& direction)
   {
      int scale = 1;
      Node* neighbour = FindNeighbour(node, direction);

      //If the neighbouring node at the same level has children,
      //it means it is a higher level and the edge scale should be increase.
      if (neighbour != nullptr && neighbour->m_isParent)
      {
         scale = 2;
      }

      return scale;
   }

   Node* FindCommonParent(Node* node, const Direction& direction)
   {

   }


   Node* FindNeighbour(Node* node, const Direction& direction)
   {
      bool foundCommonNode = false;
      int currentIndex = 0;
      int m_indices[MAX_LEVELS];

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

   Node m_rootNode;
   std::vector<Node*> m_endNodes;

   static const int NUMBER_OF_DIRECTIONS = 4;
   static const int MAX_LEVELS = 6;
   const GLint m_originLocation;
   const GLint m_sizeLocation;
   const GLint m_levelLocation;
   const GLint m_edgeScalingLocation;

   static const int NODES_PER_QUAD = 4;

};