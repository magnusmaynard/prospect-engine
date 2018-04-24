#pragma once
#include "ILight.h"

namespace Prospect
{
   class DirectionalLight_impl;
   enum class LightType;
   struct Color;

   class DirectionalLight : public ILight
   {
   public:
      DirectionalLight(const glm::vec3& direction);
      DirectionalLight(std::shared_ptr<DirectionalLight_impl>& impl);

      void SetType(const LightType& value) override;
      LightType GetType() const override;

      void SetCastShadows(const bool value) override;
      bool GetCastShadows() const override;

      void SetShadowCascades(const std::vector<float>& value);
      const std::vector<float>& GetShadowCascades() const;

      void SetPosition(const glm::vec3& value) override;
      glm::vec3 GetPosition() const override;

      void SetDirection(const glm::vec3& value) override;
      glm::vec3 GetDirection() const override;

      void SetColor(const Color& value) override;
      Color GetColor() const override;

      void SetBrightness(const float value) override;
      float GetBrightness() const override;

   private:
      std::shared_ptr<DirectionalLight_impl> m_impl;

      friend class Scene_impl;
   };
}
