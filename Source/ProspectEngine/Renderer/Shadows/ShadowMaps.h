#pragma once
#include "Renderer/Shadows/ShadowMap.h"

namespace Prospect
{
   class Camera_impl;
   class ILight_impl;
   class Scene_impl;

   struct Bounds
   {
      Bounds()
         :
         Min(std::numeric_limits<float>::max()),
         Max(std::numeric_limits<float>::lowest())
      {
      }

      glm::vec3 GetCentre() const
      {
         return (Max + Min) * 0.5f;
      }

      glm::vec3 Min;
      glm::vec3 Max;
   };

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
      float GetFarClipDepth(const int index) const;
      GLuint GetTexture() const;

   private:
      void UpdateShadowMap(DirectionalLight_impl& light);

      void UpdateShadowMapCascades(DirectionalLight_impl& light, const Camera_impl& camera);
      void BindShadowMap(const int index) const;

      ShadowMap& GetShadowMap(DirectionalLight_impl& light, const int cascadeIndex);

      GLuint m_shadowFBO;
      GLuint m_shadowTextures;

      std::vector<ShadowMap> m_shadowMaps;

      const glm::ivec2 TEXTURE_SIZE = glm::ivec2(1024, 1024);
   };
}
