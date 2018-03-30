#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Renderers/RenderDataLibrary.h"
#include "Renderer/Renderers/RenderData.h"

namespace Prospect
{
   class Atmosphere_impl;
   class GBuffer;

   struct AtmosphereRenderData : RenderData
   {
   };

   class AtmosphereRenderer
   {
   public:
      AtmosphereRenderer(ShaderLibrary& shaderLibrary);
      ~AtmosphereRenderer();

      void Render(const Atmosphere_impl& atmosphere, const GBuffer& gBuffer);

   private:
      AtmosphereShader& m_shader;

      RenderDataLibrary<AtmosphereRenderData> m_renderDataLibrary;
   };
}
