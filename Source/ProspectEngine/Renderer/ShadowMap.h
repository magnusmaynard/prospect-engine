#pragma once
#include "Scene/Lights/DirectionalLight_impl.h"

namespace Prospect
{
   class ShadowMap
   {
   public:
      ShadowMap(const DirectionalLight_impl& light);
      void Initialise();

      void Clear();
      void Bind();

      bool GetIsDirty() const;
      void SetIsDirty(const bool value) const;

      glm::mat4 GetProjection() const;
      glm::mat4 GetView() const;
      GLuint GetShadowTexture() const;

   private:
      void UpdateProjectionAndView() const;

      const DirectionalLight_impl& m_light;
      GLuint m_shadowFBO;
      GLuint m_shadowTexture;

      const glm::ivec2 TEXTURE_SIZE = glm::ivec2(1024, 1024);

      mutable glm::mat4 m_projection;
      mutable glm::mat4 m_view;
      mutable bool m_isDirty;
   };
}
