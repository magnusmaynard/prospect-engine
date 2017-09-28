#pragma once

#include <glm/mat4x4.hpp>

namespace Prospect
{
   class UniformBuffer
   {
   public:
      void Bind();
      void SetViewTransform(const glm::mat4& viewTransform);
      void SetProjectionTransform(const glm::mat4& projectionTransform);

   private:
      glm::mat4 m_viewTransform;
      glm::mat4 m_projectionTransform;
   };
}