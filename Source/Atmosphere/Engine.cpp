#include "Engine.h"

using namespace Prospect;

Engine::Engine(
   IApplication& application,
   const int width,
   const int height)
   :
   m_application(application),
   m_window(application, glm::ivec2(width, height))
{
   m_scene.CreateCamera(m_window.GetSize());
}

void Engine::Start()
{
   m_window.Open();

   m_application.OnStartup();

   while (m_window.IsOpen())
   {
      m_window.PollEvents();

      Clear();

      m_scene.Render();

      m_application.OnUpdate(m_window.GetTime());

      m_window.SwapBuffers();
   }

   m_application.OnShutdown();

   m_window.Close();
}

void Engine::SetTitle(const std::string& title)
{
   m_window.SetTitle(title);
}

void Engine::Close()
{
   m_window.Close();
}

void Engine::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Engine::SetPolygonMode(const PolygonMode& polygonMode)
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

Scene& Engine::GetScene()
{
   return m_scene;
}

glm::ivec2 Engine::GetSize() const
{
   return m_window.GetSize();
}
