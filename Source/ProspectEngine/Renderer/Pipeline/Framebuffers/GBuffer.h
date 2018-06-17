#pragma once
#include "Renderer/Pipeline/Shaders/LightingShader.h"
#include "Renderer/Pipeline/Framebuffers/Framebuffer.h"

namespace Prospect
{
   class GBuffer
   {
   public:
      GBuffer(const glm::ivec2& size);
      ~GBuffer();

      void Resize(const glm::ivec2& size);
      void Clear();
      void Bind();

      GLuint GetAlbedoTexture() const;
      GLuint GetNormalTexture() const;
      GLuint GetSpecularTexture() const;
      GLuint GetDepthTexture() const;

   private:
      void Initialize();
      void Destroy();

      const enum G_TEXTURES
      {
         G_TEXTURE_ALBEDO,
         G_TEXTURE_NORMAL,
         G_TEXTURE_SPECULAR,
         G_TEXTURE_DEPTH,
         G_TEXTURE_COUNT,
      };

      GLuint m_textures[G_TEXTURE_COUNT];

      Framebuffer m_framebuffer;
   };
}
