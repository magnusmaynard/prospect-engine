#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

namespace Prospect
{
   class ShadowMaps;

   class LightingShader : public Shader
   {
   public:
      LightingShader(const GlobalUniformBuffers& globalUniforms)
         :
         Shader(
            Resources::Shaders::QUAD_VERTEX,
            Resources::Shaders::LIGHTING_FRAGMENT),
         m_shadowMapsUniforms("ShadowMapsUniforms")
      {
         globalUniforms.Camera.Bind(GetProgram());
         globalUniforms.DirectionalLights.Bind(GetProgram());
         globalUniforms.MaterialLibrary.Bind(GetProgram());
         m_shadowMapsUniforms.Bind(GetProgram());
      }

      void Update(const ShadowMaps& shadowMaps)
      {
         m_shadowMapsUniforms.Update(shadowMaps);
      }

   private:
      UniformBuffer<ShadowMapsUniforms> m_shadowMapsUniforms;

   };
}
