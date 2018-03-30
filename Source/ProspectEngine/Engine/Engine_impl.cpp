#include "ProspectEngine_pch.h"

#include "Engine_impl.h"

#include "Scene/Scene_impl.h"
#include "Scene2D/Scene2D_impl.h"
#include "Scene/Camera_impl.h"
#include "Include/MaterialLibrary.h"
#include "Scene2D/Text_impl.h"

using namespace Prospect;
using namespace glm;

Engine_impl::Engine_impl(
   Engine& parent,
   IApplication& application,
   const ivec2& size)
   :
   m_parent(parent),
   m_application(application),
   m_window(*this, size),
   m_renderer(m_materialLibrary.GetImpl(), size),
   m_isCameraControlsEnabled(true),
   m_lastUpdateTime(0),
   m_showFPS(false)
{
   Text_impl& fpsText = m_scene2D.AddText();
   fpsText.SetPosition(ivec2(4, 0));
}

void Engine_impl::Start()
{
   OnResize(m_window.GetSize());

   m_application.OnStartup();

   unsigned int m_frameCount;

   while (m_window.IsOpen())
   {
      const double time = m_window.GetTime();
      const double elapsed = time - m_lastUpdateTime;

      m_window.PollEvents();

      if (elapsed >= TIME_PER_UPDATE)
      {
         m_lastUpdateTime = time;

         m_application.OnUpdate(elapsed);
      }

      m_scene.m_impl->Update(time);

      UpdateFPS(time);

      m_renderer.Render(time, *m_scene.m_impl, m_scene2D);

      m_window.SwapBuffers();
   }

   m_application.OnShutdown();

   m_window.Close();
}

void Engine_impl::SetTitle(const std::string& title)
{
   m_window.SetTitle(title);
}

void Engine_impl::EnableCameraControls(const bool isEnabled)
{
   m_isCameraControlsEnabled = isEnabled;
}

void Engine_impl::ShowFPS(const bool showFPS)
{
   m_showFPS = showFPS;
}

void Engine_impl::ShowWireframe(const bool showWireframe)
{
   m_renderer.ShowWireframe(showWireframe);
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

   m_renderer.Resize(size);
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
      const vec2 turnDelta = oldPosition - newPosition;
      m_scene.m_impl->GetCameraImpl().Turn(turnDelta);
   }

   m_application.OnMouseMove(oldPosition, newPosition);
}

void Engine_impl::UpdateFPS(const double time)
{
   static const double FPS_INTERVAL = 1000.0;
   static double previousTime = time;
   static unsigned long frameCount;

   frameCount++;

   if (time - previousTime >= FPS_INTERVAL)
   {
      const std::string textString = std::to_string(frameCount);

      Text_impl& text = m_scene2D.GetTextByIndex(0);
      text.SetText(textString);

      frameCount = 0;
      previousTime = time;
   }
}