#pragma once
#include <memory>
#include <glm/vec2.hpp>
#include <string>

#define PROSPECT_EXPORT __declspec(dllexport)

namespace Prospect
{
   class IApplication;
   class Engine_impl;
   enum class PolygonMode;

   class PROSPECT_EXPORT Engine
   {
   public:
      Engine(
         IApplication& application,
         const int width,
         const int height);

      void Start();
      void SetTitle(const std::string& title);
      void Close();
      void Clear();
      void SetPolygonMode(const PolygonMode& polygonMode);
      //Scene& GetScene();
      glm::ivec2 GetSize() const;

   private:
      //Using opaque pointer to impls to avoid having to include internal headers outside of dll.
      //https://en.wikibooks.org/wiki/C%2B%2B_Programming/Idioms#Pointer_To_Implementation_.28pImpl.29
      Engine_impl* m_impl;
   };
}
