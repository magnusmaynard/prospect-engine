#include "Engine_impl.h"

#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include <glm/vec2.hpp>
#include <iostream>
#include "Include/MaterialLibrary.h"

using namespace Prospect;
using namespace glm;

Engine_impl::Engine_impl(
   Engine& parent,
   IApplication& application,
   const int width,
   const int height)
   :
   m_parent(parent),
   m_application(application),
   m_window(*this, ivec2(width, height)),
   m_isCameraControlsEnabled(true)
{
}

void Engine_impl::Start()
{
   m_window.Open();

   m_renderer.Setup();

   m_application.OnStartup();

   while (m_window.IsOpen())
   {
      double milliseconds = m_window.GetTime();
      double elapsed = milliseconds - m_lastUpdateTime;

      m_window.PollEvents();

      if (elapsed >= TIME_PER_UPDATE)
      {
         m_lastUpdateTime = milliseconds;

         m_application.OnUpdate(elapsed);
      }

      m_renderer.Render(milliseconds, *m_scene.m_impl);

      m_window.SwapBuffers();
   }

   m_application.OnShutdown();

   m_window.Close();
}

void Engine_impl::SetTitle(const std::string& title)
{
   m_window.SetTitle(title);
}

void Engine_impl::EnableCameraControls(bool isEnabled)
{
   m_isCameraControlsEnabled = isEnabled;
}

void Engine_impl::ShowFPS(bool showFPS)
{
   m_renderer.ShowFPS(showFPS);
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

void Engine_impl::OnResize(const ivec2& size)
{
   m_scene.m_impl->GetCameraImpl().SetSize(size);
}

void Engine_impl::OnKeyDown(const Key& key, const KeyModifier& modifier)
{
   m_application.OnKeyDown(key, modifier);
}

void Engine_impl::OnKeyUp(const Key& key, const KeyModifier& modifier)
{
   m_application.OnKeyUp(key, modifier);
}

void Engine_impl::OnMouseMove(const vec2& newPosition, const vec2& oldPosition)
{
   if (m_isCameraControlsEnabled)
   {
      vec2 turnDelta = oldPosition - newPosition;
      m_scene.m_impl->GetCameraImpl().Turn(turnDelta);
   }

   m_application.OnMouseMove(oldPosition, newPosition);
}
