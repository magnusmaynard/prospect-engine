#include "Window.h"

#include <iostream>
#include "RendererDefines.h"

using namespace Prospect;

Window::Window(IApplication& application, const glm::ivec2& size):
   m_application(application),
   m_size(size)
{
}

void Window::Open()
{
   if (!glfwInit())
   {
      exit(EXIT_FAILURE);
   }

   glfwSetErrorCallback(ErrorCallback);

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

   m_window = glfwCreateWindow(m_size.x, m_size.y, DEFAULT_TITLE.c_str(), nullptr, nullptr);
   if (!m_window)
   {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(m_window);

   if (glewInit())
   {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   //Set user pointer so static KeyCallback can access member variable.
   glfwSetWindowUserPointer(m_window, &m_application);
   glfwSetKeyCallback(m_window, KeyCallback);

   int width, height;
   glfwGetFramebufferSize(m_window, &width, &height);
   glViewport(0, 0, width, height);
   glfwSwapInterval(1);
}

void Window::SetTitle(const std::string& title)
{
   glfwSetWindowTitle(m_window, title.c_str());
}

bool Window::IsOpen() const
{
   return !glfwWindowShouldClose(m_window);
}

void Window::PollEvents() const
{
   glfwPollEvents();
}

void Window::SwapBuffers() const
{
   glfwSwapBuffers(m_window);
}

void Window::Close() const
{
   glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::Destroy() const
{
   glfwDestroyWindow(m_window);

   glfwTerminate();
   exit(EXIT_SUCCESS);
}

unsigned Window::GetTime() const
{
   return static_cast<unsigned int>(glfwGetTime());
}

glm::ivec2 Window::GetSize() const
{
   return m_size;
}

void Window::ErrorCallback(int error, const char* description)
{
   std::cerr << "Error: " << description << std::endl;
}

void Window::KeyCallback(GLFWwindow* window, int glfwKey, int glfwScancode, int glfwAction, int glfwModifer)
{
   //Get user pointer so non-static app variable can be accessed in static callback.
   IApplication* application = static_cast<IApplication*>(glfwGetWindowUserPointer(window));

   const Key key = ConvertGLFWKey(glfwKey);
   const KeyModifier modifier = ConvertGLFWModifier(glfwModifer);

   switch (glfwAction)
   {
   case GLFW_PRESS:
      {
         application->OnKeyDown(key, modifier);
         break;
      }
   case GLFW_RELEASE:
      {
         //Do nothing.
         break;
      }
   case GLFW_REPEAT:
      {
         //Do nothing.
         break;
      }
   default:
      {
         break;
      }
   }
}

Key Window::ConvertGLFWKey(int glfwKey)
{
   //TODO: More keys.
   switch (glfwKey)
   {
   case(GLFW_KEY_W):
      {
         return Key::W;
      }
   case(GLFW_KEY_ESCAPE):
      {
         return Key::Escape;
      }
   default:
      {
         return Key::None;
      }
   }
}

KeyModifier Window::ConvertGLFWModifier(int glfwModifer)
{
   switch (glfwModifer)
   {
   case(GLFW_MOD_SHIFT):
      {
         return KeyModifier::Shift;
      }
   case(GLFW_MOD_CONTROL):
      {
         return KeyModifier::Control;
      }
   case(GLFW_MOD_ALT):
      {
         return KeyModifier::Alt;
      }
   default:
      {
         return KeyModifier::None;
      }
   }
}
