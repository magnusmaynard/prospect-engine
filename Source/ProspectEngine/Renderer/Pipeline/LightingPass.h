#pragma once
#include "Renderer/Pipeline/Shaders/LightingShader.h"

namespace Prospect
{
   class ShadowMap;
   class ShaderLibrary;
   class GBuffer;

   class LightingPass
   {
   public:
      LightingPass(
         ShaderLibrary& shaderLibrary,
         const GBuffer& gbuffer);

      void Render(const ShadowMap& shadowMap);

   private:
      LightingShader& m_shader;

      const GBuffer& m_gBuffer;
   };
}
