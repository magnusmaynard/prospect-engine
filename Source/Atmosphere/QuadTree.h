#pragma once
#include <vector>
#include <memory>
#include "Node.h"

class QuadTree
{
public:
   QuadTree(
      const glm::vec3& origin,
      const float size,
      const int lod,
      const GLint originLocation,
      const GLint sizeLocation,
      const GLint lodLocation)
      :
      m_rootNode(origin, size, lod),
      m_originLocation(originLocation),
      m_sizeLocation(sizeLocation),
      m_lodLocation(lodLocation)
      {
      }

      void Draw(const glm::vec3& camera)
   {
      Draw(camera, m_rootNode);
   }

private:
   void Draw(
      const glm::vec3& camera,
      Node& node)
   {
      float distance = glm::length(node.GetOrigin() - camera);

      node.Clear(); //TODO: optimize.

      if (node.GetLod() < MAX_LOD &&
         distance < node.GetSize() * 4.0)
      {
         node.Split();
      }

      if (node.IsParent())
      {
         //Draw child nodes.
         Draw(camera, node.GetChild(0));
         Draw(camera, node.GetChild(1));
         Draw(camera, node.GetChild(2));
         Draw(camera, node.GetChild(3));
      }
      else
      {
         //Draw this node.
         glUniform3fv(m_originLocation, 1, &node.GetOrigin()[0]);
         glUniform1f(m_sizeLocation, node.GetSize());
         glUniform1f(m_lodLocation, node.GetLod());

         glPatchParameteri(GL_PATCH_VERTICES, 4);
         glDrawArrays(GL_PATCHES, 0, 4);
      }
   }

   const int MAX_LOD = 6;
   const GLint m_originLocation;
   const GLint m_sizeLocation;
   const GLint m_lodLocation;

   Node m_rootNode;
};
