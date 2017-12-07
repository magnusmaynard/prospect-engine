#pragma once

namespace Prospect
{
   class DepthTexture
   {
   public:
      DepthTexture();
      ~DepthTexture();

      void Update() const;
      void Bind(const int textureUnit) const;
      void Resize(const glm::ivec2& size);

   private:
      void CreateTexture();
      void DeleteTexture();

      glm::ivec2 m_size;
      GLuint m_depthTexture;
   };
}