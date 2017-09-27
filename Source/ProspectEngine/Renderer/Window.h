#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Include/Key.h"

#include <glm/vec2.hpp>
#include "Include/IApplication.h"
#include <string>

namespace Prospect
{
   class Engine_impl;

   class Window
   {
   public:
      Window::Window(Engine_impl& engine, const glm::ivec2& size);

      void Open();

      void SetTitle(const std::string& title);

      bool IsOpen() const;

      void PollEvents() const;

      void SwapBuffers() const;

      void Close() const;

      void Destroy() const;

      unsigned int GetTime() const;
      glm::ivec2 GetSize() const;

   private:
      static void GLFWErrorCallback(int error, const char* description);
      static void GLFWKeyCallback(GLFWwindow* glfwWindow, int glfwKey, int glfwScancode, int glfwAction, int glfwModifer);
      static void GLFWWindowSizeCallback(GLFWwindow* glfwWindow, int width, int height);
      static void GLFWCursorPosCallback(GLFWwindow* glfwWindow, double xPosition, double yPosition);
      static void GLFWCursorEnterCallback(GLFWwindow* glfwWindow, int hasEntered);

      static Window& GetWindow(GLFWwindow* glfwWindow);

      static Key ConvertGLFWKey(int glfwKey);

      static KeyModifier ConvertGLFWModifier(int glfwModifer);

      Engine_impl& m_engine;
      GLFWwindow* m_window;
      const glm::ivec2 m_size;
      glm::vec2 m_previousMousePosition;
      bool m_isMouseInsideWindow;
   };
}
