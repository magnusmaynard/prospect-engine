#pragma once
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
   QuadTree()
      :
      m_parent(nullptr),
      m_index(0),
      m_lod(0)
   {
   }

private:
   QuadTree(QuadTree* parent, const int index, const int lod)
      :
      m_parent(parent),
      m_index(index),
      m_lod(lod)
   {
   }

public:


   void UpdateEdgeScaling()
   {
      if(IsParent())
      {
         GetChild(0).UpdateEdgeScaling();
         GetChild(1).UpdateEdgeScaling();
         GetChild(2).UpdateEdgeScaling();
         GetChild(3).UpdateEdgeScaling();
      }
      else
      {
         m_leftLevelDifference = CalculateLevelDifference(Direction::Left);
         m_rightLevelDifference = CalculateLevelDifference(Direction::Right);
         m_upLevelDifference = CalculateLevelDifference(Direction::Up);
         m_downLevelDifference = CalculateLevelDifference(Direction::Down);
      }
   }

private:

   QuadTree& GetChild(const int index)
   {
      return m_children[index];
   }
   void Divide()
   {
      m_children.clear();
      m_children.push_back(QuadTree(this, 0, m_lod + 1));
      m_children.push_back(QuadTree(this, 1, m_lod + 1));
      m_children.push_back(QuadTree(this, 2, m_lod + 1));
      m_children.push_back(QuadTree(this, 3, m_lod + 1));
   }

   int CalculateLevelDifference(const Direction& direction)
   {
      int lodDifference = 0;
      std::stack<int> indices;
      QuadTree* neighbour = FindNeighbour(direction, indices);

      if(neighbour == nullptr)
      {
         lodDifference = 0;
      }
      else if (neighbour->IsParent())
      {
         //Neighbour lod cannot be greater than current, due to algorithm limits.
         //Just say it is one greater.
         lodDifference = -1;
      }
      else
      {
         lodDifference = m_lod - neighbour->m_lod; //0 or 1+;
      }

      return lodDifference;
   }

   QuadTree* FindNeighbour(const Direction& direction, std::stack<int>& indices)
   {
      //Edge node.
      if(m_parent == nullptr)
      {
         return nullptr;
      }

      //TODO: refactor using bit switching
      switch(m_index)
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
      if(IsParent() && indices.size() > 0)
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
   int m_lod;
   std::vector<QuadTree> m_children;
   int m_leftLevelDifference = 0;
   int m_rightLevelDifference = 0;
   int m_upLevelDifference = 0;
   int m_downLevelDifference = 0;
};
