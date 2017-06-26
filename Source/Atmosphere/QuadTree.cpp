#include "QuadTree.h"

QuadTree::QuadTree(
   const glm::vec3& origin,
   const float size,
   const GLint originLocation,
   const GLint sizeLocation,
   const GLint levelLocation,
   const GLint edgeScalingLocation)
   :
   m_rootNode(nullptr, 0, 0, origin, size),
   m_originLocation(originLocation),
   m_sizeLocation(sizeLocation),
   m_levelLocation(levelLocation),
   m_edgeScalingLocation(edgeScalingLocation)
{
}

void QuadTree::Update(const glm::vec3& camera)
{
   m_endNodes.clear();
   m_rootNode.Update(camera, m_endNodes);
}

void QuadTree::Draw()
{
   for (auto& node : m_endNodes)
   {
      //Update edge scaling for this node.
      node->UpdateEdgeScaling();

      //Draw this node.
      glUniform3fv(m_originLocation, 1, &node->Origin()[0]);
      glUniform1f(m_sizeLocation, node->Size());
      glUniform1i(m_levelLocation, node->Level());
      glUniform4iv(m_edgeScalingLocation, 1, &node->Edges()[0]);

      glPatchParameteri(GL_PATCH_VERTICES, 4);
      glDrawArrays(GL_PATCHES, 0, 4);
   }
}
