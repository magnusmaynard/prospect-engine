#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include "Window.h"
#include "Scene.h"
#include "PolygonMode.h"
#include "IApplication.h"
#include "Defaults.h"

namespace Prospect
{
   class Engine
   {
   public:
      Engine(
         IApplication& application,
         const int width = DEFAULT_WIDTH,
         const int height = DEFAULT_HEIGHT);

      void Start();
      void SetTitle(const std::string& title);
      void Close();
      void Clear();
      void SetPolygonMode(const PolygonMode& polygonMode);
      Scene& GetScene();
      glm::ivec2 GetSize() const;

   private:
      IApplication& m_application;
      Window m_window;
      Scene m_scene;

      std::function<void()> m_startupCallback;
      std::function<void()> m_shutdownCallback;
      std::function<void(unsigned int)> m_updateCallback;
   };
}