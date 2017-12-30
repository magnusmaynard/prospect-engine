#pragma once
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
         const glm::ivec2& size);
      ~Engine();

      void Start();
      void SetTitle(const std::string& title);
      void EnableCameraControls(bool isEnabled);
      void ShowFPS(bool showFPS);
      void ShowWireframe(bool showWireframe);
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
