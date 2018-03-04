#pragma once
#include <glm/vec3.hpp>

namespace Prospect
{
   enum class LightType;

   class ILight_impl
   {
   public:
      virtual ~ILight_impl() {};

      virtual void SetType(const LightType& value) = 0;
      virtual LightType GetType() const = 0;

      virtual void SetCastShadows(const bool value) = 0;
      virtual bool GetCastShadows() const = 0;

      virtual void SetShadowMapIndex(const int value) = 0;
      virtual int GetShadowMapIndex() const = 0;

      virtual bool GetIsDirty() const = 0;
      virtual void SetIsDirty(const bool value) = 0;

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
