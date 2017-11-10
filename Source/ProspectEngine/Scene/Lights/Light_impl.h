#pragma once
#include "Include/Color.h"

namespace Prospect
{
   class Light_impl
   {
   public:
      Light_impl(
         const glm::vec3& position,
         const glm::vec3& direction);

      void SetPosition(const glm::vec3& value);
      glm::vec3 GetPosition() const;

      void SetDirection(const glm::vec3& value);
      glm::vec3 GetDirection() const;

      void SetColor(const Color& value);
      Color GetColor() const;

   private:
      glm::vec3 m_position;
      glm::vec3 m_direction;
      float m_brightness;
      Color m_color;
   };
}
