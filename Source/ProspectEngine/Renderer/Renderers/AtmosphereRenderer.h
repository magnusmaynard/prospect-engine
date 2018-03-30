#pragma once

#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Pipeline/ShaderLibrary.h"

namespace Prospect
{
   class Atmosphere_impl;
   class GBuffer;

   struct AtmosphereRenderable
   {
   };

   class AtmosphereRenderer
   {
   public:
      AtmosphereRenderer(ShaderLibrary& shaderLibrary);
      ~AtmosphereRenderer();

      void Render(const Atmosphere_impl& atmosphere, const GBuffer& gBuffer);

   private:
      AtmosphereRenderable& GetRenderable(const Atmosphere_impl& atmosphere);
      void UpdateUniformsIfDirty();

      AtmosphereShader& m_shader;

      std::map<unsigned, AtmosphereRenderable> m_atmosphereRenderables;
   };
}
