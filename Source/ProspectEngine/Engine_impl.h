#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Include/Engine.h"
#include "Include/IApplication.h"
#include "Include/Scene.h"
#include "Renderer/Window.h"
#include "Scene/Scene_impl.h"
#include "Renderer/Renderer.h"
#include "Defaults.h"

namespace Prospect
{
   enum class PolygonMode;

   class Engine_impl
   {
   public:
      Engine_impl(
         Engine& parent,
         IApplication& application,
         const int width = DEFAULT_WIDTH,
         const int height = DEFAULT_HEIGHT);

      Engine& GetParent();
      const Engine& GetParent() const;

      void Start();
      void SetTitle(const std::string& title);
      void Close();
      Scene& GetScene();
      glm::ivec2 GetSize() const;

   private:
      Engine& m_parent;

      IApplication& m_application;
      Window m_window;
      Scene m_scene;
      Renderer m_renderer;
   };
}
