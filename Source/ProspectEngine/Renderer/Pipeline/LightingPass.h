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

      void Render();

   private:
      LightingShader& m_shader;

      const GBuffer& m_gBuffer;
   };
}
