#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

#include <functional>
#include "Key.h"
#include "IApplication.h"

namespace Prospect
{
   class Window
   {
   public:
      Window(IApplication& application, const glm::ivec2& size);

      void Open();

      void SetTitle(const std::string& title);

      bool IsOpen() const;

      void PollEvents();

      void SwapBuffers();

      void Close();

      void Destroy();

      unsigned int GetTime() const;

      glm::ivec2 GetSize() const;

   private:
      static void ErrorCallback(int error, const char* description);

      static void KeyCallback(GLFWwindow* window, int glfwKey, int glfwScancode, int glfwAction, int glfwModifer);

      static Key ConvertGLFWKey(int glfwKey);

      static KeyModifier ConvertGLFWModifier(int glfwModifer);

      IApplication& m_application;
      GLFWwindow* m_window;
      const glm::ivec2 m_size;
   };
}