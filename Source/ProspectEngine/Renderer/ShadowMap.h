#pragma once
#include "Scene/Lights/DirectionalLight_impl.h"

namespace Prospect
{
   class ShadowMap
   {
   public:
      ShadowMap();

      void Update(const DirectionalLight_impl& light);
      glm::mat4 GetShadowMatrix() const;
      glm::mat4 GetViewMatrix() const;
      glm::mat4 GetProjectionMatrix() const;

   private:
      mutable glm::mat4 m_shadowMatrix;
      mutable glm::mat4 m_viewMatrix;
      mutable glm::mat4 m_projectionMatrix;
   };
}
