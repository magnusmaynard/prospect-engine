#include "ProspectEngine_pch.h"

#include "Renderer/Window.h"

#include "Renderer/RendererDefines.h"

#include "Engine/Engine_impl.h"

using namespace Prospect;
using namespace glm;

Window::Window(Engine_impl& engine, const ivec2& size)
   :
   m_engine(engine),
   m_window(nullptr),
   m_size(size),
   m_isMouseInsideWindow(false),
   m_enableVSync(true)
{
   Open();
}

void Window::Open()
{
   if (!glfwInit())
   {
      exit(EXIT_FAILURE);
   }

   glfwSetErrorCallback(GLFWErrorCallback);

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#ifdef _DEBUG
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

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

   //Set user pointer so static function can access member variable.
   glfwSetWindowUserPointer(m_window, this);

   glfwSetKeyCallback(m_window, GLFWKeyCallback);
   glfwSetWindowSizeCallback(m_window, GLFWWindowSizeCallback);
   glfwSetCursorPosCallback(m_window, GLFWCursorPosCallback);
   glfwSetCursorEnterCallback(m_window, GLFWCursorEnterCallback);

   int width, height;
   glfwGetFramebufferSize(m_window, &width, &height);
   glViewport(0, 0, width, height);

   EnableVSync(m_enableVSync);
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

double Window::GetTime() const
{
   return glfwGetTime() * 1000.0;
}

ivec2 Window::GetSize() const
{
   return m_size;
}

void Window::EnableVSync(bool enableVSync)
{
   glfwSwapInterval(enableVSync ? 1 : 0);
}

void Window::GLFWErrorCallback(int error, const char* description)
{
   std::cerr << "Error: " << description << std::endl;
}

Window& Window::GetWindow(GLFWwindow* glfwWindow)
{
   //Get user pointer so non-static variable can be accessed in static callback.
   Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

   if(window == nullptr)
   {
      throw std::exception("Error: Null GLFW window pointer.");
   }

   return *window;
}

void Window::GLFWKeyCallback(GLFWwindow* glfwWindow, int glfwKey, int glfwScancode, int glfwAction, int glfwModifer)
{
   Engine_impl& engine = GetWindow(glfwWindow).m_engine;

   const Key key = ConvertGLFWKey(glfwKey);
   const KeyModifier modifier = ConvertGLFWModifier(glfwModifer);

   switch (glfwAction)
   {
      case GLFW_PRESS:
      {
         engine.OnKeyDown(key, modifier);
         break;
      }
      case GLFW_RELEASE:
      {
         engine.OnKeyUp(key, modifier);
         break;
      }
      case GLFW_REPEAT:
      {
         engine.OnKeyDown(key, modifier);
         break;
      }
      default:
      {
         break;
      }
   }
}

void Window::GLFWWindowSizeCallback(GLFWwindow* glfwWindow, int width, int height)
{
   Engine_impl& engine = GetWindow(glfwWindow).m_engine;

   glViewport(0, 0, width, height);

   engine.OnResize(ivec2(width, height));
}

void Window::GLFWCursorPosCallback(GLFWwindow* glfwWindow, double xPosition, double yPosition)
{
   Window& window = GetWindow(glfwWindow);

   vec2 mousePosition(xPosition, yPosition);

   if(window.m_isMouseInsideWindow == false)
   {
      window.m_previousMousePosition = mousePosition;
      window.m_isMouseInsideWindow = true;
   }

   window.m_engine.OnMouseMove(mousePosition, window.m_previousMousePosition);

   window.m_previousMousePosition = mousePosition;
}

void Window::GLFWCursorEnterCallback(GLFWwindow* glfwWindow, int hasEntered)
{
   Window& window = GetWindow(glfwWindow);

   if (hasEntered == false)
   {
      window.m_isMouseInsideWindow = false;
   }
}

Key Window::ConvertGLFWKey(int glfwKey)
{
   //TODO: Support more keys.
   switch (glfwKey)
   {
      case(GLFW_KEY_1):
         return Key::D1;
      case(GLFW_KEY_2):
         return Key::D2;
      case(GLFW_KEY_3):
         return Key::D3;
      case(GLFW_KEY_4):
         return Key::D4;
      case(GLFW_KEY_5):
         return Key::D5;
      case(GLFW_KEY_6):
         return Key::D6;
      case(GLFW_KEY_7):
         return Key::D7;
      case(GLFW_KEY_8):
         return Key::D8;
      case(GLFW_KEY_9):
         return Key::D9;
      case(GLFW_KEY_0):
         return Key::D0;
      case(GLFW_KEY_W):
         return Key::W;
      case(GLFW_KEY_S):
         return Key::S;
      case(GLFW_KEY_A):
         return Key::A;
      case(GLFW_KEY_D):
         return Key::D;
      case(GLFW_KEY_C):
         return Key::C;
      case(GLFW_KEY_SPACE):
         return Key::Space;
      case(GLFW_KEY_ESCAPE):
         return Key::Escape;
      case (GLFW_KEY_PRINT_SCREEN):
         return Key::PrintScreen;
      default:
      {
         std::cout << "Key not supported: " << glfwKey << std::endl;
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
      case(0):
      {
         return KeyModifier::None;
      }
      default:
      {
         std::cout << "Modifier not supported: " << glfwModifer << std::endl;
         return KeyModifier::None;
      }
   }
}
