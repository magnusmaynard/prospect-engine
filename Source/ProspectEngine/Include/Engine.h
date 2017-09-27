#pragma once

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
      Engine(
         IApplication& application,
         const int width,
         const int height);
      ~Engine();

      void Start();
      void SetTitle(const std::string& title);
      void SetEnableCameraControls(bool isEnabled);
      void Close();
      glm::ivec2 GetSize() const;

      Scene& GetScene();
      MeshLibrary& GetMeshLibrary();
      MaterialLibrary& GetMaterialLibrary();

   private:
      //Using opaque pointer to impls to avoid having to include internal headers outside of dll.
      std::unique_ptr<Engine_impl> m_impl;
   };
}
