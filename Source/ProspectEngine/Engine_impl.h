#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer/Window.h"
#include "Scene/Scene.h"
#include "Include/IApplication.h"
#include "Defaults.h"

namespace Prospect
{
   enum class PolygonMode;

   class Engine_impl
   {
   public:
      Engine_impl(
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
   };
}