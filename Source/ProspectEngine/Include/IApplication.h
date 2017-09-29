#pragma once

#include <glm/vec2.hpp>

namespace Prospect
{
   enum class KeyModifier;
   enum class Key;

   class IApplication
   {
   public:
      virtual ~IApplication() {}

      virtual void OnStartup() = 0;
      virtual void OnShutdown() = 0;
      virtual void OnUpdate(double timeElapsed) = 0;
      virtual void OnKeyDown(const Key& key, const KeyModifier& modifier) = 0;
      virtual void OnKeyUp(const Key& key, const KeyModifier& modifier) = 0;
      virtual void OnMouseMove(const glm::vec2& newPosition, const glm::vec2& oldPosition) = 0;
   };
}