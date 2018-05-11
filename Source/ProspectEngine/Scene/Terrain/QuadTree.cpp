#include "ProspectEngine_pch.h"

#include "QuadTree.h"
#include "Renderer/Debugger/Debug.h"

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

   UpdateClosestEndNode(position);
}

int QuadTree::FindClosestEndNodeIndex(const glm::vec3& position) const
{
   int closestEndNodeIndex = 0;
   float closestEndNodeDistance = m_endNodes[closestEndNodeIndex]->DistanceTo(position);

   for (size_t i = 0; i < m_endNodes.size(); i++)
   {
      const float endNodeDistance = m_endNodes[i]->DistanceTo(position);

      if (endNodeDistance < closestEndNodeDistance)
      {
         closestEndNodeIndex = static_cast<int>(i);
         closestEndNodeDistance = endNodeDistance;
      }
   }

   return closestEndNodeIndex;
}

bool QuadTree::UpdateClosestEndNode(const glm::vec3& position)
{
   const int closestEndNodeIndex = FindClosestEndNodeIndex(position);
   if (m_closestEndNodeIndex != closestEndNodeIndex)
   {
      m_closestEndNodeIndex = closestEndNodeIndex;
      return true;
   }

   return false;
}

const std::vector<Node*>& QuadTree::GetEndNodes() const
{
   return m_endNodes;
}

bool QuadTree::RequiresUpdate(const glm::vec3& position)
{
   Node* closestyEndNode = m_endNodes[m_closestEndNodeIndex];

   return  closestyEndNode->IsLODInvalid(position) || UpdateClosestEndNode(position);
}
