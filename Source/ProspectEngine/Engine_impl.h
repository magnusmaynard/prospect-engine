#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Include/Engine.h"
#include "Include/IApplication.h"
#include "Include/Scene.h"
#include "Include/MeshLibrary.h"
#include "Include/MaterialLibrary.h"

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

namespace Prospect
{
   class Scene_impl;

   class Engine_impl
   {
   public:
      //Public
      void Start();
      void SetTitle(const std::string& title);
      void SetEnableCameraControls(bool isEnabled);

      void Close();
      glm::ivec2 GetSize() const;

      Scene& GetScene();
      MeshLibrary& GetMeshLibrary();
      MaterialLibrary& GetMaterialLibrary();

      //Internal
      Engine_impl(
         Engine& parent,
         IApplication& application,
         const int width,
         const int height);

      void OnResize(const glm::ivec2& size);
      void OnKeyDown(const Key& key, const KeyModifier& modifier);
      void OnKeyUp(const Key& key, const KeyModifier& modifier);
      void OnMouseMove(const glm::vec2& newPosition, const glm::vec2& oldPosition);

      Scene_impl& GetSceneImpl();

   private:
      Engine& m_parent;

      IApplication& m_application;
      Window m_window;
      Scene m_scene;
      MeshLibrary m_meshLibrary;
      MaterialLibrary m_materialLibrary;
      Renderer m_renderer;

      bool m_isCameraControlsEnabled;
   };
}
