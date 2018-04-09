#pragma once
#include "Include/Color.h"
#include "Include/Lights/LightType.h"
#include "Scene/Lights/ILight_impl.h"

namespace Prospect
{
   class DirectionalLight_impl : public ILight_impl
   {
   public:
      //Public
      DirectionalLight_impl(const glm::vec3& direction);

      void SetType(const LightType& value) override;
      LightType GetType() const override;

      void SetCastShadows(const bool value) override;
      bool GetCastShadows() const override;

      void SetShadowCascadeCount(const int value);
      int GetShadowCascadeCount() const;

      void SetPosition(const glm::vec3& value) override;
      glm::vec3 GetPosition() const override;

      void SetDirection(const glm::vec3& value) override;
      glm::vec3 GetDirection() const override;

      void SetColor(const Color& value) override;
      Color GetColor() const override;

      void SetBrightness(const float value) override;
      float GetBrightness() const override;

      //Internal
      void SetShadowMapIndex(const int value) override;
      int GetShadowMapIndex() const override;

      bool GetIsDirty() const override;
      void SetIsDirty(const bool value) override;

   private:
      void MakeDirty();

      LightType m_type;
      bool m_castShadows;
      int m_shadowMapIndex;
      bool m_isDirty;
      int m_shadowCascadeCount;

      glm::vec3 m_position;
      glm::vec3 m_direction;
      float m_brightness;
      Color m_color;
   };
}
