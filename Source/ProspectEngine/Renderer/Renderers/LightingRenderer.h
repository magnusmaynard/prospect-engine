#pragma once

#include "Renderer/Pipeline/Shaders/LightingShader.h"

namespace Prospect
{
   class ShaderLibrary;
   class GBuffer;
   class ShadowMaps;

   class LightingRenderer
   {
   public:
      LightingRenderer(ShaderLibrary& shaderLibrary);

      void Render(const GBuffer& gbuffer, const ShadowMaps& shadowMaps);

   private:
      LightingShader& m_shader;
   };
}
