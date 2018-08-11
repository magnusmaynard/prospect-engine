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
      float Radius;
      float Distance;
   };

   class SunRenderer
   {
   public:
      SunRenderer(ShaderLibrary& shaderLibrary, MaterialLibrary_impl& materialLibrary);
      ~SunRenderer();

      void Render(const Atmosphere_impl& atmosphere);

   private:
      static void Initialise(SunRenderData& renderData);
      static void Dispose(SunRenderData& renderData);

      Material m_material;

      SunShader& m_shader;
      RenderDataLibrary<SunRenderData> m_renderDataLibrary;
   };
}
