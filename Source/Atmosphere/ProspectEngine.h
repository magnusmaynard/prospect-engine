#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include "Window2.h"
#include "Scene.h"
#include "Camera.h"
#include "PolygonMode.h"
#include "Keys.h"

class ProspectEngine
{
public:
   ProspectEngine(const int width, const int height)
      :
      m_window(width, height)
   {
      m_scene.CreateCamera(glm::ivec2(width, height));
   }

   void Start()
   {
      m_window.Open();

      m_startupCallback();

      while (m_window.IsOpen())
      {
         m_window.PollEvents();

         Clear();

         m_scene.Render();

         m_updateCallback(m_window.GetTime());

         m_window.SwapBuffers();
      }

      m_shutdownCallback();

      m_window.Close();
   }

   void Clear()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   }

   void SetStartup(const std::function<void()>& startupCallback)
   {
      m_startupCallback = startupCallback;
   }

   void SetShutdown(const std::function<void()>& shutdownCallback)
   {
      m_shutdownCallback = shutdownCallback;
   }

   void SetUpdate(const std::function<void(unsigned int)>& updateCallback)
   {
      m_updateCallback = updateCallback;
   }

   void SetKeyDown(const std::function<void(const Keys& key)>& keyDownCallback)
   {
      m_window.SetKeyDown(keyDownCallback);
   }

   void SetPolygonMode(const PolygonMode& polygonMode)
   {
      int mode = -1;
      switch (polygonMode)
      {
         case PolygonMode::Point:
         {
            mode = GL_POINT;
            break;
         }
         case PolygonMode::Line:
         {
            mode = GL_LINE;
            break;
         }
         case PolygonMode::Fill:
         {
            mode = GL_FILL;
            break;
         }
         default:
         {
            throw std::exception("Invalid PolygonMode.");
         }
      }

      glPolygonMode(GL_FRONT_AND_BACK, mode);
   }

   Scene& GetScene()
   {
      return m_scene;
   }

   glm::ivec2 GetSize() const
   {
      return m_window.GetSize();
   }

private:

   Window2 m_window;
   Scene m_scene;

   std::function<void()> m_startupCallback;
   std::function<void()> m_shutdownCallback;
   std::function<void(unsigned int)> m_updateCallback;
};
