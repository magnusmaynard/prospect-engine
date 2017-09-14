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
   class MeshLibrary;
   class MaterialLibrary;

   class Engine_impl;

   class Engine
   {
   public:
      EXPORT_DLL Engine(
         IApplication& application,
         const int width,
         const int height);
      EXPORT_DLL ~Engine();

      EXPORT_DLL void Start();
      EXPORT_DLL void SetTitle(const std::string& title);
      EXPORT_DLL void Close();
      EXPORT_DLL glm::ivec2 GetSize() const;

      EXPORT_DLL Scene& GetScene();
      EXPORT_DLL MeshLibrary& GetMeshLibrary();
      EXPORT_DLL MaterialLibrary& GetMaterialLibrary();

   private:
      //Using opaque pointer to impls to avoid having to include internal headers outside of dll.
      std::unique_ptr<Engine_impl> m_impl;
   };
}
