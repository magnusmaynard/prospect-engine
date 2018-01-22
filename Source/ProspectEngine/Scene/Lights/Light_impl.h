#pragma once
#include "Include/Color.h"
#include "Include/Lights/LightType.h"

namespace Prospect
{
   class Light_impl
   {
   public:
      Light_impl(
         const glm::vec3& position,
         const glm::vec3& direction,
         const LightType& type);

      void SetPosition(const glm::vec3& value);
      glm::vec3 GetPosition() const;

      void SetDirection(const glm::vec3& value);
      glm::vec3 GetDirection() const;

      void SetColor(const Color& value);
      Color GetColor() const;

      void SetBrightness(const float value);
      float GetBrightness() const;

      void SetRange(const float value);
      float GetRange() const;

      void SetAngle(const float value);
      float GetAngle() const;

      void SetType(const LightType& value);
      LightType GetType() const;

   private:
      glm::vec3 m_position;
      glm::vec3 m_direction;
      float m_brightness;
      float m_range;
      float m_angle;
      Color m_color;
      LightType m_type;
   };
}
