#pragma once
#include <GL/glew.h>

struct QuadTreeUniformLocations
{
   QuadTreeUniformLocations(
      const GLint originLocation,
      const GLint normalLocation,
      const GLint leftLocation,
      const GLint topLocation,
      const GLint sizeLocation,
      const GLint levelLocation,
      const GLint edgeScalingLocation)
      :
      m_origin(originLocation),
      m_normal(normalLocation),
      m_left(leftLocation),
      m_top(topLocation),
      m_size(sizeLocation),
      m_level(levelLocation),
      m_edgeScaling(edgeScalingLocation)
   {}

   GLint Origin() const
   {
      return m_origin;
   }

   GLint Normal() const
   {
      return m_normal;
   }

   GLint Left() const
   {
      return m_left;
   }

   GLint Top() const
   {
      return m_top;
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
   const GLint m_normal;
   const GLint m_left;
   const GLint m_top;
   const GLint m_size;
   const GLint m_level;
   const GLint m_edgeScaling;
};