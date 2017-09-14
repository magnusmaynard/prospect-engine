#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Include/Engine.h"
#include "Include/IApplication.h"
#include "Include/Scene.h"
#include "Include/MeshLibrary.h"
#include "Include/MaterialLibrary.h"

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

namespace Prospect
{
   enum class PolygonMode;

   class Engine_impl
   {
   public:
      Engine_impl(
         Engine& parent,
         IApplication& application,
         const int width,
         const int height);

      Engine& GetParent();
      const Engine& GetParent() const;

      void Start();
      void SetTitle(const std::string& title);
      void Close();
      glm::ivec2 GetSize() const;

      Scene& GetScene();
      MeshLibrary& GetMeshLibrary();
      MaterialLibrary& GetMaterialLibrary();

   private:
      Engine& m_parent;

      IApplication& m_application;
      Window m_window;
      Scene m_scene;
      MeshLibrary m_meshLibrary;
      MaterialLibrary m_materialLibrary;
      Renderer m_renderer;
   };
}
