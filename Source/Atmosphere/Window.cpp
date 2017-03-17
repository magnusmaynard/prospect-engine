#include "Window.h"
#include "IApplication.h"

#include <iostream>

void Window::ErrorCallback(int error, const char* description)
{
   std::cerr << "Error: " << description << std::endl;
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window(IApplication* app)
   :
   m_app(app)
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

   GLFWwindow* window = glfwCreateWindow(m_size.x, m_size.y, "Atmosphere", nullptr, nullptr);
   if (!window)
   {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(window);

   if (glewInit())
   {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwSetKeyCallback(window, KeyCallback);

   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   glViewport(0, 0, width, height);
   glfwSwapInterval(1);

   m_app->Startup();

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();

      m_app->Render(glfwGetTime());

      glfwSwapBuffers(window);
   }

   m_app->Shutdown();

   glfwDestroyWindow(window);

   glfwTerminate();
   exit(EXIT_SUCCESS);
}