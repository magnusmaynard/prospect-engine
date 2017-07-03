#include "QuadTree.h"

QuadTree::QuadTree(
   const glm::vec3& origin,
   const glm::vec3& normal,
   const glm::vec3& left,
   const glm::vec3& top,
   const float size,
   const QuadTreeUniformLocations& locations)
   :
   m_rootNode(nullptr, 0, 0, origin, left, top, size),
   m_normal(normal),
   m_left(left),
   m_top(top),
   m_locations(locations)
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
      glUniform3fv(m_locations.Origin(), 1, &node->Origin()[0]);
      glUniform1f(m_locations.Size(), node->Size());
      glUniform1i(m_locations.Level(), node->Level());
      glUniform4iv(m_locations.EdgeScaling(), 1, &node->Edges()[0]);
      glUniform3fv(m_locations.Normal(), 1, &m_normal[0]);
      glUniform3fv(m_locations.Left(), 1, &m_left[0]);
      glUniform3fv(m_locations.Top(), 1, &m_top[0]);

      glPatchParameteri(GL_PATCH_VERTICES, 4);
      glDrawArrays(GL_PATCHES, 0, 4);
   }
}
