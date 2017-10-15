#pragma once
#include <GL/glew.h>

namespace Prospect
{
   struct QuadTreeUniformLocations
   {
      QuadTreeUniformLocations(
         const GLint originLocation,
         const GLint sizeLocation,
         const GLint levelLocation,
         const GLint edgeScalingLocation)
         :
         m_origin(originLocation),
         m_size(sizeLocation),
         m_level(levelLocation),
         m_edgeScaling(edgeScalingLocation)
      {}

      GLint Origin() const
      {
         return m_origin;
      }

      GLint Size() const
      {
         return m_size;
      }

      GLint Level() const
      {
         return m_level;
      }

      GLint EdgeScaling() const
      {
         return m_edgeScaling;
      }

   private:
      const GLint m_origin;
      const GLint m_size;
      const GLint m_level;
      const GLint m_edgeScaling;
   };
}