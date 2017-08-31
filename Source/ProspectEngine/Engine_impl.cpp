#include "Engine_impl.h"

#include <glm/vec2.hpp>

using namespace Prospect;

Engine_impl::Engine_impl(
   Engine& parent, 
   IApplication& application,
   const int width,
   const int height)
   :
   m_parent(parent),
   m_application(application),
   m_window(application, glm::ivec2(width, height))
{
   m_scene.GetImpl().CreateCamera(m_window.GetSize());
}

Engine& Engine_impl::GetParent()
{
   return m_parent;
}

const Engine& Engine_impl::GetParent() const
{
   return m_parent;
}

void Engine_impl::Start()
{
   m_window.Open();

   m_application.OnStartup();

   while (m_window.IsOpen())
   {
      m_window.PollEvents();

      m_renderer.Render(m_scene.GetImpl());

      m_application.OnUpdate(m_window.GetTime());

      m_window.SwapBuffers();
   }

   m_application.OnShutdown();

   m_window.Close();
}

void Engine_impl::SetTitle(const std::string& title)
{
   m_window.SetTitle(title);
}

void Engine_impl::Close()
{
   m_window.Close();
}

//void Engine_impl::Clear()
//{
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//}

//void Engine_impl::SetPolygonMode(const PolygonMode& polygonMode)
//{
//   int mode = -1;
//   switch (polygonMode)
//   {
//      case PolygonMode::Point:
//      {
//         mode = GL_POINT;
//         break;
//      }
//      case PolygonMode::Line:
//      {
//         mode = GL_LINE;
//         break;
//      }
//      case PolygonMode::Fill:
//      {
//         mode = GL_FILL;
//         break;
//      }
//      default:
//      {
//         throw std::exception("Invalid PolygonMode.");
//      }
//   }
//
//   glPolygonMode(GL_FRONT_AND_BACK, mode);
//}

Scene& Engine_impl::GetScene()
{
   return m_scene;
}

glm::ivec2 Engine_impl::GetSize() const
{
   return m_window.GetSize();
}