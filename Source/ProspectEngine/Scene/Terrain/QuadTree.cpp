#include "ProspectEngine_pch.h"

#include "QuadTree.h"

using namespace Prospect;

QuadTree::QuadTree(
   const glm::vec3& origin,
   const float size)
   :
   m_rootNode(nullptr, 0, 0, origin, size),
   m_endNodes({ &m_rootNode }),
   m_closestEndNodeIndex(0)
{
}

void QuadTree::ForceUpdate(const glm::vec3& position)
{
   //Update all nodes.
   m_endNodes.clear();
   m_rootNode.Update(position, m_endNodes);

   for (auto& node : m_endNodes)
   {
      node->UpdateEdgeScaling();
   }
}

int QuadTree::FindClosestEndNodeIndex(const glm::vec3& position) const
{
   int closestEndNodeIndex = 0;
   float closestEndNodeDistance = m_endNodes[closestEndNodeIndex]->DistanceTo(position);

   for (int i = 0; i < m_endNodes.size(); i++)
   {
      const float endNodeDistance = m_endNodes[i]->DistanceTo(position);

      if (endNodeDistance < closestEndNodeDistance)
      {
         closestEndNodeIndex = i;
         closestEndNodeDistance = endNodeDistance;
      }
   }

   return closestEndNodeIndex;
}

bool QuadTree::NewClosestEndNode(const glm::vec3& position)
{
   const int closestEndNodeIndex = FindClosestEndNodeIndex(position);
   if (m_closestEndNodeIndex != closestEndNodeIndex)
   {
      m_closestEndNodeIndex = closestEndNodeIndex;
      return true;
   }

   return false;
}

void QuadTree::Update(const glm::vec3& position)
{
   Node* endNode = m_endNodes[m_closestEndNodeIndex];

   if(endNode->IsLODInvalid(position) ||
      NewClosestEndNode(position))
   {
      ForceUpdate(position);
   }
}

const std::vector<Node*>& QuadTree::GetEndNodes() const
{
   return m_endNodes;
}
