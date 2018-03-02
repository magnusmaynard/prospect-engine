#pragma once
#include "Renderer/Pipeline/Shaders/LightingShader.h"

namespace Prospect
{
   class ShaderLibrary;
   class GBuffer;

   class LightingPass
   {
   public:
      LightingPass(
         ShaderLibrary& shaderLibrary,
         const GBuffer& gbuffer);

      void Render(const GLuint m_shadowTexture, const glm::mat4& lightMVP);

   private:
      LightingShader& m_shader;

      const GBuffer& m_gBuffer;
   };
}
