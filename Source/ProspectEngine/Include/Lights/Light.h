#pragma once

namespace Prospect
{
   enum class LightType;
   class Light_impl;
   struct Color;

   class Light
   {
   public:
      Light(
         const glm::vec3& position,
         const glm::vec3& direction,
         const LightType& type);
      Light(std::shared_ptr<Light_impl>& impl);

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
      std::shared_ptr<Light_impl> m_impl;

      friend class Scene_impl;
   };
}
