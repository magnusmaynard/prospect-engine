#pragma once
#include <glm/vec3.hpp>

namespace Prospect
{
   enum class LightType;
   struct Color;

   class ILight
   {
   public:
      virtual ~ILight() {};

      virtual void SetType(const LightType& value) = 0;
      virtual LightType GetType() const = 0;

      virtual void SetPosition(const glm::vec3& value) = 0;
      virtual glm::vec3 GetPosition() const = 0;

      virtual void SetDirection(const glm::vec3& value) = 0;
      virtual glm::vec3 GetDirection() const = 0;

      virtual void SetColor(const Color& value) = 0;
      virtual Color GetColor() const = 0;

      virtual void SetBrightness(const float value) = 0;
      virtual float GetBrightness() const = 0;
   };
}
