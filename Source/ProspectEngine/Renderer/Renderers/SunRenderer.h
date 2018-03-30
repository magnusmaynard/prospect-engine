#pragma once

#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Pipeline/Shaders/SunShader.h"
#include "AtmosphereRenderer.h"
#include "RenderDataLibrary.h"
#include "Renderer/Renderers/RenderData.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;

   struct SunRenderData : RenderData
   {
      GLuint PointsBuffer;
      GLuint VAO;
      glm::mat4 Translation;
      std::vector<glm::vec3> Points;
      glm::vec3 Color;
      float Radius;
      float Distance;
   };

   class SunRenderer
   {
   public:
      SunRenderer(ShaderLibrary& shaderLibrary);
      ~SunRenderer();

      void Render(const Atmosphere_impl& atmosphere);

   private:
      static void Initialise(SunRenderData& renderData);
      static void Dispose(SunRenderData& renderData);

      SunShader& m_shader;
      RenderDataLibrary<SunRenderData> m_renderDataLibrary;
   };
}
