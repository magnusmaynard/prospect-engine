#include "Engine_impl.h"

#include "Scene/Scene_impl.h"
#include <glm/vec2.hpp>
#include <iostream>

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

glm::ivec2 Engine_impl::GetSize() const
{
   return m_window.GetSize();
}

Scene& Engine_impl::GetScene()
{
   return m_scene;
}

MeshLibrary& Engine_impl::GetMeshLibrary()
{
   return m_meshLibrary;
}