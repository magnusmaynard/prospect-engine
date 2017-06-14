#pragma once
#include <vector>
#include <memory>

class QuadTree
{
public:
   QuadTree(const glm::vec3& origin, const float size, const int lod)
      :
      m_origin(origin),
      m_size(size),
      m_lod(lod)
   {
   }

   void Draw(
      const glm::vec3& camera,
      const GLint originLocation,
      const GLint sizeLocation,
      const GLint lodLocation)
   {
      float distance = glm::length(m_origin - camera);

      m_nodes.clear(); //TODO: optimize.

      if (m_lod < MAX_LOD &&
         distance < m_size * 4.0)
      {
         //Divide into 4 child nodes.
         float childSize = m_size * 0.5;
         float childSizeHalf = childSize * 0.5;
         float childLod = m_lod + 1;

         m_nodes.push_back(QuadTree(
            m_origin + glm::vec3(-childSizeHalf, 0, childSizeHalf),
            childSize,
            childLod));
         m_nodes.push_back(QuadTree(
            m_origin + glm::vec3(childSizeHalf, 0, childSizeHalf),
            childSize,
            childLod));
         m_nodes.push_back(QuadTree(
            m_origin + glm::vec3(childSizeHalf, 0, -childSizeHalf),
            childSize,
            childLod));
         m_nodes.push_back(QuadTree(
            m_origin + glm::vec3(-childSizeHalf, 0, -childSizeHalf),
            childSize,
            childLod));
      }

      if (m_nodes.size() > 0)
      {
         //Draw child nodes.
         for (auto& node : m_nodes)
         {
            node.Draw(camera, originLocation, sizeLocation, lodLocation);
         }
      }
      else
      {
         //Draw this node.
         glUniform3fv(originLocation, 1, &m_origin[0]);
         glUniform1f(sizeLocation, m_size);
         glUniform1f(lodLocation, m_lod);

         glPatchParameteri(GL_PATCH_VERTICES, 4);
         glDrawArrays(GL_PATCHES, 0, 4);
      }
   }

private:
   const int MAX_LOD = 6;
   glm::vec3 m_origin;
   float m_size;
   int m_lod;

   std::vector<QuadTree> m_nodes;
};