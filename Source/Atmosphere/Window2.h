#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

#include <functional>
#include <iostream>

#include <glm/vec2.hpp>
#include "Keys.h"

class Window2
{
public:
   Window2(const int width, const int height)
      :
      m_size(width, height)
   {
   }

   void Open()
   {
      if (!glfwInit())
      {
         exit(EXIT_FAILURE);
      }

      glfwSetErrorCallback(ErrorCallback);

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

      m_window = glfwCreateWindow(m_size.x, m_size.y, "Prospect Engine", nullptr, nullptr);
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

      //Set user pointer so static KeyCallback can access memember variable.
      glfwSetWindowUserPointer(m_window, this);
      glfwSetKeyCallback(m_window, KeyCallback);

      int width, height;
      glfwGetFramebufferSize(m_window, &width, &height);
      glViewport(0, 0, width, height);
      glfwSwapInterval(1);

   }

   bool IsOpen()
   {
      return !glfwWindowShouldClose(m_window);
   }

   void PollEvents()
   {
      glfwPollEvents();
   }

   void SwapBuffers()
   {
      glfwSwapBuffers(m_window);
   }

  void Close()
  {
      glfwDestroyWindow(m_window);

      glfwTerminate();
      exit(EXIT_SUCCESS);
   }

   unsigned int GetTime() const
   {
      return static_cast<unsigned int>(glfwGetTime());
   }

   glm::ivec2 GetSize() const
   {
      return m_size;
   }

   void SetKeyDown(const std::function<void(const Keys& key)>& keyDownCallback)
   {
      m_keyDownCallback = keyDownCallback;
   }

private:
   static void ErrorCallback(int error, const char* description)
   {
      std::cerr << "Error: " << description << std::endl;
   }

   static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
   {
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      {
         glfwSetWindowShouldClose(window, GLFW_TRUE);
      }

      //Get user pointer so non-static app variable can be accessed in static callback.
      Window2* window2 = static_cast<Window2*>(glfwGetWindowUserPointer(window));
      window2->m_keyDownCallback(Keys::W); //TODO: convert keys, should be reference.
   }

   GLFWwindow* m_window;
   const glm::ivec2 m_size;

   std::function<void(const Keys& key)> m_keyDownCallback;
};
