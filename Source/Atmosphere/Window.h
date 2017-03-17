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
   void Open();

   glm::vec2 GetSize() const { return m_size; }

private:
   static void Window::ErrorCallback(int error, const char* description);
   static void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
   IApplication* m_app;

   glm::vec2 m_size = glm::vec2(1000, 600); //glm::vec2(640, 480);
};
