#include "ProspectEngine_pch.h"

#include "QuadTree.h"

using namespace Prospect;

QuadTree::QuadTree(
   const glm::vec3& origin,
   const float size,
   const QuadTreeUniformLocations& locations)
   :
   m_rootNode(nullptr, 0, 0, origin, size),
   m_locations(locations)
{
}

void QuadTree::Update(const glm::vec3& cameraPosition, const glm::vec3& cameraDirection)
{
   m_endNodes.clear();
   m_rootNode.Update(cameraPosition, cameraDirection, m_endNodes);

   for (auto& node : m_endNodes)
   {
      //Update edge scaling for this node.
      node->UpdateEdgeScaling();
   }
}

void QuadTree::Draw()
{
   for (auto& node : m_endNodes)
   {
      //Draw this node.
      glUniform3fv(m_locations.Origin(), 1, &node->Origin()[0]);
      glUniform1f(m_locations.Size(), node->Size());
      glUniform1i(m_locations.Level(), node->Level());
      glUniform4iv(m_locations.EdgeScaling(), 1, &node->Edges()[0]);

      glPatchParameteri(GL_PATCH_VERTICES, 4);
      glDrawArrays(GL_PATCHES, 0, 4);
   }
}
