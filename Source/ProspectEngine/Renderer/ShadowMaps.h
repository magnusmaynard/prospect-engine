#pragma once
#include "Renderer/ShadowMap.h"

namespace Prospect
{
   class ILight_impl;
   class Scene_impl;

   class ShadowMaps
   {
   public:
      ShadowMaps();
      ~ShadowMaps();

      void Clear();
      void Update(Scene_impl& scene);

      int Count() const;
      void Bind(int index);

      glm::mat4 GetShadowMatrix(const int index) const;
      glm::mat4 GetProjectionMatrix(const int index) const;
      glm::mat4 GetViewMatrix(const int index) const;
      GLuint GetTexture() const;

   private:
      void UpdateShadowMap(DirectionalLight_impl& light);
      void BindShadowMap(const int index) const;

      GLuint m_shadowFBO;
      GLuint m_shadowTextures;

      std::vector<ShadowMap> m_shadowMaps;

      const glm::ivec2 TEXTURE_SIZE = glm::ivec2(1024, 1024);
   };
}
