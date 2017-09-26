#include "Engine_impl.h"

#include "Scene/Scene_impl.h"
#include <glm/vec2.hpp>
#include <iostream>
#include "Include/MaterialLibrary.h"

using namespace Prospect;

Engine_impl::Engine_impl(
   Engine& parent, 
   IApplication& application,
   const int width,
   const int height)
   :
   m_parent(parent),
   m_application(application),
   m_window(this, glm::ivec2(width, height))
{
}

void Engine_impl::Start()
{
   m_window.Open();

   m_application.OnStartup();

   while (m_window.IsOpen())
   {
      m_window.PollEvents();

      m_renderer.Render(*m_scene.m_impl);

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

MaterialLibrary& Engine_impl::GetMaterialLibrary()
{
   return m_materialLibrary;
}

Scene_impl& Engine_impl::GetSceneImpl()
{
   return *m_scene.m_impl;
}

void Engine_impl::OnResize(const glm::ivec2& size)
{
   m_scene.GetCamera().SetSize(size);
}

void Engine_impl::OnKeyDown(const Key& key, const KeyModifier& modifier)
{
   m_application.OnKeyDown(key, modifier);
}

void Engine_impl::OnKeyUp(const Key& key, const KeyModifier& modifier)
{
   m_application.OnKeyUp(key, modifier);
}

void Engine_impl::OnMouseMove(const glm::vec2& position)
{
}
