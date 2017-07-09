#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include "IApplication.h"
#include <glm/vec2.hpp>

class Window
{
public:
   Window(IApplication* app);
   void Open() const;

   glm::vec2 GetSize() const { return m_size; }

private:
   static void Window::ErrorCallback(int error, const char* description);
   static void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
   static void Window::MouseMoveCallback(GLFWwindow* window, double xPosition, double yPosition);

public:
   IApplication* m_app;

   glm::vec2 m_size = glm::vec2(1200, 600);
};
