#pragma once
#include <vector>
#include <memory>
#include <glm/vec3.hpp>

class Node
{
public:
   Node(const glm::vec3& origin, const float size, const int lod)
      :
      m_origin(origin),
      m_size(size),
      m_lod(lod)
   {
   }

   glm::vec3 GetOrigin() const
   {
      return m_origin;
   }

   float GetSize() const
   {
      return m_size;
   }

   int GetLod() const
   {
      return m_lod;
   }

   bool IsParent() const
   {
      return m_nodes.size() > 0;
   }

   Node& GetChild(const int index)
   {
      return m_nodes[index];
   }

   //Clear all child nodes.
   void Clear()
   {
      m_nodes.clear();
   }

   //Divide into 4 child nodes.
   void Split()
   {
      float childSize = m_size * 0.5;
      float childSizeHalf = childSize * 0.5;
      float childLod = m_lod + 1;

      m_nodes.push_back(Node(
         m_origin + glm::vec3(-childSizeHalf, 0, childSizeHalf),
         childSize,
         childLod));
      m_nodes.push_back(Node(
         m_origin + glm::vec3(childSizeHalf, 0, childSizeHalf),
         childSize,
         childLod));
      m_nodes.push_back(Node(
         m_origin + glm::vec3(childSizeHalf, 0, -childSizeHalf),
         childSize,
         childLod));
      m_nodes.push_back(Node(
         m_origin + glm::vec3(-childSizeHalf, 0, -childSizeHalf),
         childSize,
         childLod));
   }

private:
   glm::vec3 m_origin;
   float m_size;
   int m_lod;

   std::vector<Node> m_nodes;

};