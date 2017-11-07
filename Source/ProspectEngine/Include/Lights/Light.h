#pragma once
#include "Include/Color.h"

namespace Prospect
{
   class Light
   {
   public:
      Light(
         const glm::vec3& position,
         const glm::vec3& direction);

      void SetPosition(const glm::vec3& position);
      glm::vec3 GetPosition() const;

      void SetDirection(const glm::vec3& direction);
      glm::vec3 GetDirection() const;

      void SetBrightness(const float brightness);
      float GetBrightness() const;

      void SetColor(const Color& color);
      Color GetColor() const;

   private:
      glm::vec3 m_position;
      glm::vec3 m_direction;
      float m_brightness;
      Color m_color;
   };
}
