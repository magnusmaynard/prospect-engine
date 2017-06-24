#pragma once
#include <GL/glew.h>
#include <vector>
#include <stack>

enum class Direction
{
   Up,
   Down,
   Left,
   Right
};

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
      m_parent(nullptr),
      m_index(0),
      m_level(0),
      m_origin(origin),
      m_size(size),
      m_originLocation(originLocation),
      m_sizeLocation(sizeLocation),
      m_levelLocation(levelLocation),
      m_levelDifferencesLocation(levelDifferencesLocation)
   {
   }

private:
   QuadTree(
      QuadTree* parent,
      const int index,
      const int level,
      const glm::vec3& origin,
      const float size,
      const GLint originLocation,
      const GLint sizeLocation,
      const GLint levelLocation,
      const GLint levelDifferencesLocation)
      :
      m_parent(parent),
      m_index(index),
      m_level(level),
      m_origin(origin),
      m_size(size),
      m_originLocation(originLocation),
      m_sizeLocation(sizeLocation),
      m_levelLocation(levelLocation),
      m_levelDifferencesLocation(levelDifferencesLocation)
   {
   }

public:
   void UpdateLevels(const glm::vec3& camera)
   {
      float distance = glm::length(m_origin - camera);

      m_children.clear(); //TODO: optimize.

      if (m_level < MAX_LOD &&
         distance < m_size * 2.0)
      {
         Divide();

         m_children[0].UpdateLevels(camera);
         m_children[1].UpdateLevels(camera);
         m_children[2].UpdateLevels(camera);
         m_children[3].UpdateLevels(camera);
      }
   }

   void UpdateAdjacentLevelDifferences()
   {
      if (IsParent())
      {
         GetChild(0).UpdateAdjacentLevelDifferences();
         GetChild(1).UpdateAdjacentLevelDifferences();
         GetChild(2).UpdateAdjacentLevelDifferences();
         GetChild(3).UpdateAdjacentLevelDifferences();
      }
      else
      {
         m_levelDifferences.clear();
         m_levelDifferences.push_back(CalculateScales(Direction::Left));
         m_levelDifferences.push_back(CalculateScales(Direction::Right));
         m_levelDifferences.push_back(CalculateScales(Direction::Up));
         m_levelDifferences.push_back(CalculateScales(Direction::Down));
      }
   }

   void Draw(const glm::vec3& camera)
   {
      if (IsParent())
      {
         //Draw child nodes.
         GetChild(0).Draw(camera);
         GetChild(1).Draw(camera);
         GetChild(2).Draw(camera);
         GetChild(3).Draw(camera);
      }
      else
      {
         //Draw this node.
         glUniform3fv(m_originLocation, 1, &m_origin[0]);
         glUniform1f(m_sizeLocation, m_size);
         glUniform1f(m_levelLocation, m_level);
         glUniform4iv(m_levelDifferencesLocation, 1, &m_levelDifferences[0]);

         glPatchParameteri(GL_PATCH_VERTICES, 4);
         glDrawArrays(GL_PATCHES, 0, 4);
      }
   }

private:

   QuadTree& GetChild(const int index)
   {
      return m_children[index];
   }
   void Divide()
   {
      float childSize = m_size * 0.5;
      float childSizeHalf = childSize * 0.5;
      float childLevel = m_level + 1;

      m_children.clear();

      m_children.push_back(QuadTree(
         this,
         0,
         childLevel,
         m_origin + glm::vec3(-childSizeHalf, 0, childSizeHalf),
         childSize,
         m_originLocation,
         m_sizeLocation,
         m_levelLocation,
         m_levelDifferencesLocation));

      m_children.push_back(QuadTree(
         this,
         1,
         childLevel,
         m_origin + glm::vec3(childSizeHalf, 0, childSizeHalf),
         childSize,
         m_originLocation,
         m_sizeLocation,
         m_levelLocation,
         m_levelDifferencesLocation));

      m_children.push_back(QuadTree(
         this,
         2,
         childLevel,
         m_origin + glm::vec3(-childSizeHalf, 0, -childSizeHalf),
         childSize,
         m_originLocation,
         m_sizeLocation,
         m_levelLocation,
         m_levelDifferencesLocation));

      m_children.push_back(QuadTree(
         this,
         3,
         childLevel,
         m_origin + glm::vec3(childSizeHalf, 0, -childSizeHalf),
         childSize,
         m_originLocation,
         m_sizeLocation,
         m_levelLocation,
         m_levelDifferencesLocation));
   }

   int CalculateScales(const Direction& direction)
   {
      int scale = 1;
      std::stack<int> indices;
      QuadTree* neighbour = FindNeighbour(direction, indices);

      if (neighbour != nullptr && neighbour->IsParent())
      {
         scale = 2;
      }

      return scale;
   }

   QuadTree* FindNeighbour(const Direction& direction, std::stack<int>& indices)
   {
      //Edge node.
      if (m_parent == nullptr)
      {
         return nullptr;
      }

      //TODO: refactor using bit switching
      switch (m_index)
      {
      case 0:
         switch (direction)
         {
         case Direction::Right:
            indices.push(1);
            return m_parent->FindChild(indices); //halt
         case Direction::Left:
            indices.push(1);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Down:
            indices.push(2);
            return m_parent->FindChild(indices); //halt
         case Direction::Up:
            indices.push(2);
            return m_parent->FindNeighbour(direction, indices);
         }
         break;
      case 1:
         switch (direction)
         {
         case Direction::Right:
            indices.push(0);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Left:
            indices.push(0);
            return m_parent->FindChild(indices); //halt
         case Direction::Down:
            indices.push(3);
            return m_parent->FindChild(indices); //halt
         case Direction::Up:
            indices.push(3);
            return m_parent->FindNeighbour(direction, indices);
         }
         break;
      case 2:
         switch (direction)
         {
         case Direction::Right:
            indices.push(3);
            return m_parent->FindChild(indices); //halt
         case Direction::Left:
            indices.push(3);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Down:
            indices.push(0);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Up:
            indices.push(0);
            return m_parent->FindChild(indices); //halt
         }
         break;
      case 3:
         switch (direction)
         {
         case Direction::Right:
            indices.push(2);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Left:
            indices.push(2);
            return m_parent->FindChild(indices); //halt
         case Direction::Down:
            indices.push(1);
            return m_parent->FindNeighbour(direction, indices);
         case Direction::Up:
            indices.push(1);
            return m_parent->FindChild(indices); //halt
         }
         break;
      }
   }

   //search for child at a gives set of indices, relative to the current node.
   QuadTree* FindChild(std::stack<int>& indices)
   {
      if (IsParent() && indices.size() > 0)
      {
         auto index = indices.top();
         indices.pop();

         m_children[index].FindChild(indices);
      }
      else
      {
         return this;
      }
   }

   bool IsParent() const
   {
      return m_children.size() > 0;
   }

   QuadTree* m_parent;
   int m_index;
   int m_level;
   std::vector<QuadTree> m_children;
   std::vector<int> m_levelDifferences;

   glm::vec3 m_origin;
   float m_size;
   const int MAX_LOD = 6;
   const GLint m_originLocation;
   const GLint m_sizeLocation;
   const GLint m_levelLocation;
   const GLint m_levelDifferencesLocation;

};