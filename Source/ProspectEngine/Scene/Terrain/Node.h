#pragma once

namespace Prospect
{
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
         const float size);

      //Updates the child nodes, such that they are more detailed closer to the
      //given position. The child nodes are divided until they are the
      //appropraite level of detail.
      void Update(const glm::vec3& position, std::vector<Node*>& endNodes);

      //Updates the edges scaling factors of all the child nodes.
      //Edge scaling represents the difference between the LOD of a node and
      //it's 4 neighbouring nodes.
      void UpdateEdgeScaling();

      //Nodes current level of detail it not correct for the given position.
      //This means it requires updating.
      bool IsLODInvalid(const glm::vec3& position) const;

      float DistanceTo(const glm::vec3 position) const;

   private:
      //Node is not detailed enough for the given position.
      //Division of the nodes into quads is required.
      bool RequiresDivide(const glm::vec3& position) const;

      //Node is too detailed for the given position.
      //Merging of the nodes into a single quads is required.
      bool RequiresMerge(const glm::vec3& position) const;

      //Divide Node into 4 child nodes.
      void Divide();

      //TODO: Remove current index from update, just use lod.
      //Finds the nearest neighbouring Node in the QuadTree in a given direction.
      Node* FindNeighbour(const Direction& direction);

      static const int NUMBER_OF_EDGES = 4;
      static const int NUMBER_OF_CHILDREN = 4;
      static const int MAX_LEVEL = 6;
      static const int NUMBER_OF_LEVELS = MAX_LEVEL + 1;
      static const int DIVISION_THRESHOLD = 6;

      Node* m_parent;
      int m_index;
      int m_level;
      glm::vec3 m_origin; //TODO: These are the same as QuadTree, use those instead of storing them locally.
      float m_size;

      bool m_isParent = false;
      std::unique_ptr<Node> m_children[NUMBER_OF_CHILDREN];
      glm::ivec4 m_edgeScaling;
      bool m_edgeScalingIsDirty = true;

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

      glm::ivec4 Edges() const
      {
         return m_edgeScaling;
      }
   };
}