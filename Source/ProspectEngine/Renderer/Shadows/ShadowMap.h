#pragma once
#include "Scene/Lights/DirectionalLight_impl.h"

namespace Prospect
{
   struct Bounds;

   class ShadowMap
   {
   public:
      ShadowMap();

      void Update(const Bounds& bounds, const glm::vec3& position, const glm::vec3& direction, const float farClipDepth);
      glm::mat4 GetShadowMatrix() const;
      glm::mat4 GetViewMatrix() const;
      glm::mat4 GetProjectionMatrix() const;
      float GetFarClipDepth() const;

   private:
      mutable glm::mat4 m_shadowMatrix;
      mutable glm::mat4 m_viewMatrix;
      mutable glm::mat4 m_projectionMatrix;
      float m_farClipDepth;
   };
}
