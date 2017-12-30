#pragma once
#include "Renderer/Pipeline/Shaders/GBufferShader.h"

namespace Prospect
{
   class ShaderLibrary;

   class GBuffer
   {
   public:
      GBuffer(ShaderLibrary& shaderLibrary, const glm::ivec2& size);
      ~GBuffer();

      //Update sizes of framebuffers.
      void Resize(const glm::ivec2& size);

      //Clear all framebuffers.
      void Clear();

      //Bind framebuffers ready for geometry pass
      void Bind();

      //Perform lighting calculation and present to screen.
      void Present();

   private:
      void Initialize(const glm::ivec2& size);
      void Destroy();

      const enum G_TEXTURES
      {
         G_TEXTURE_ALBEDO,
         G_TEXTURE_NORMAL,
         G_TEXTURE_SPECULAR,
         G_TEXTURE_DEPTH,
         G_TEXTURE_COUNT,
      };

      GLuint m_FBO;
      GLuint m_textures[G_TEXTURE_COUNT];

      GBufferShader& m_shader;
   };
}
