#pragma once
#include "Renderer/Pipeline/Shaders/LightingShader.h"

namespace Prospect
{
   class ShaderLibrary;
   class GBuffer;
   class ShadowMaps;

   class LightingPass
   {
   public:
      LightingPass(
         ShaderLibrary& shaderLibrary,
         const GBuffer& gbuffer,
         const ShadowMaps& shadowMaps);

      void Render();

   private:
      LightingShader& m_shader;

      const GBuffer& m_gBuffer;
      const ShadowMaps& m_shadowMaps;
   };
}
