#pragma once
#include "RenderData.h"
#include "Renderer/Pipeline/Shaders/GodRaysShader.h"
#include "RenderDataLibrary.h"

namespace Prospect
{
   class DisplayBuffer;
   class ShaderLibrary;
   class GBuffer;

   class GodRaysRenderer
   {
   public:
      GodRaysRenderer(ShaderLibrary& shaderLibrary);
      ~GodRaysRenderer();

      void Render(const GBuffer& gBuffer, const DisplayBuffer& displayBuffer, const glm::vec3& sunPosition);

   private:
      GodRaysShader& m_shader;
   };
}
