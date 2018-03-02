#pragma once
#include "Scene/Lights/Light_impl.h"

namespace Prospect
{
   class ShaderLibrary;

   class ShadowMap
   {
   public:
      ShadowMap(
         ShaderLibrary& shaderLibrary,
         const Light_impl& light);

      void Render();

   private:
      void UpdateLightMVP();

      const Light_impl& m_light;
      GLuint m_shadowFBO;
      GLuint m_shadowTexture;

      //ShadowMapShader& m_shader;

      glm::mat4 m_lightMVP;

      const glm::ivec2 TEXTURE_SIZE = glm::ivec2(1000, 1000);
   };
}
