#include "ProspectEngine_pch.h"

#include "QuadTree.h"

using namespace Prospect;

QuadTree::QuadTree(
   const glm::vec3& origin,
   const float size)
   :
   m_rootNode(nullptr, 0, 0, origin, size)
{
}

void QuadTree::Update(const glm::vec3& cameraPosition)
{
   m_endNodes.clear();
   m_rootNode.Update(cameraPosition, m_endNodes);

   for (auto& node : m_endNodes)
   {
      node->UpdateEdgeScaling();
   }
}


const std::vector<Node*>& QuadTree::GetEndNodes() const
{
   return m_endNodes;
}
