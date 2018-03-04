#pragma once
#include "Renderer/Pipeline/Shaders/LightingShader.h"

namespace Prospect
{
   class GBuffer
   {
   public:
      GBuffer(const glm::ivec2& size);
      ~GBuffer();

      //Update sizes of framebuffers.
      void Resize(const glm::ivec2& size);

      //Clear all framebuffers.
      void Clear();

      //Bind framebuffers ready for geometry pass
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

      GLuint m_FBO;
      GLuint m_textures[G_TEXTURE_COUNT];
      glm::ivec2 m_size;
   };
}
