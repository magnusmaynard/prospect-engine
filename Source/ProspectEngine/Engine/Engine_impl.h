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
#include "Scene2D/Scene2D_impl.h"

namespace Prospect
{
   class Scene_impl;

   class Engine_impl
   {
   public:
      //Public
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

      //Internal
      Engine_impl(
         Engine& parent,
         IApplication& application,
         const glm::ivec2& size);

      void OnResize(const glm::ivec2& size);
      void OnKeyDown(const Key& key, const KeyModifier& modifier);
      void OnKeyUp(const Key& key, const KeyModifier& modifier);
      void OnMouseMove(const glm::vec2& newPosition, const glm::vec2& oldPosition);

      Scene_impl& GetSceneImpl();

   private:
      void UpdateFPS(const double time);

      Engine& m_parent;

      IApplication& m_application;
      Scene m_scene;
      Scene2D_impl m_scene2D;

      MaterialLibrary m_materialLibrary;
      MeshLibrary m_meshLibrary;
      Window m_window;
      Renderer m_renderer;

      bool m_isCameraControlsEnabled;
      double m_lastUpdateTime;
      bool m_showFPS;
   };
}
