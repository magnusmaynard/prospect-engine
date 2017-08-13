#pragma once

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
      virtual void OnUpdate(const unsigned int time) = 0;
      virtual void OnKeyDown(const Key& key, const KeyModifier& modifier) = 0;
   };
}