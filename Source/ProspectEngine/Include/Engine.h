#pragma once
#include "Defines.h"
#include <glm/vec2.hpp>
#include <string>
#include <memory>

namespace Prospect
{
   class IApplication;
   enum class PolygonMode;
   class Scene;

   class Engine_impl;

   class Engine
   {
   public:
      EXPORT_API Engine(
         IApplication& application,
         const int width,
         const int height);
      EXPORT_API ~Engine();

      EXPORT_API void Start();
      EXPORT_API void SetTitle(const std::string& title);
      EXPORT_API void Close();
      EXPORT_API Scene& GetScene();
      EXPORT_API glm::ivec2 GetSize() const;

   private:
      //Using opaque pointer to impls to avoid having to include internal headers outside of dll.
      std::unique_ptr<Engine_impl> m_impl;
   };
}
