#include "Application.h"

#include <glm/vec4.hpp>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/normal.hpp>

//TODO: This constructor never gets passed window init because of render loop. Remove it somehow?
Application::Application()
   :
   m_window(this)
{
   m_window.Open();
}

void Application::Startup()
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   ////Enable shaders to overlay and blend colors.
   glBlendFunc(GL_SRC_ALPHA, GL_ONE); //GL_ONE_MINUS_SRC_ALPHA
   //glEnable(GL_BLEND); //TODO: blend effects the same object drawn over itself. Enable depth test?

   //glCullFace(GL_BACK);
   //glEnable(GL_CULL_FACE);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //View.
   UpdateViewMatrix();

   //Projection.
   float aspect = m_window.GetSize().x / m_window.GetSize().y;
   m_projection = glm::perspective(65.0f, aspect, 0.0001f, 10000.0f); //55

   m_terrain = std::make_unique<Terrain>();
   //m_atmosphere = std::make_unique<Atmosphere>();
}

void Application::Shutdown()
{
}

void Application::Render(const double time)
{
   //Clear
   //glClearBufferfv(GL_COLOR, 0, &m_backgroundColor[0]);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   m_eyePosition.z += sin(time) * 5.0;
   UpdateViewMatrix();

   ////Earth
   m_terrain->Draw(m_view, m_projection, m_sunDirection);

   //glEnable(GL_BLEND);

   ////Atmosphere
   //m_atmosphere->Draw(
   //   m_view,
   //   m_projection,
   //   m_window.GetSize(),
   //   m_sunDirection,
   //   m_eyePosition, //TODO: Can eyePosition be derived from view?
   //   m_earthPosition);

   //glDisable(GL_BLEND);
}


void Application::OnKeyPressed(int key, int action, int mods)
{
   const float rotationIncrement = 0.02f;
   if (key == 49) //1
   {
      m_sunDirection = glm::rotateY(m_sunDirection, -rotationIncrement);
   }

   if (key == 50) //2
   {
      m_sunDirection = glm::rotateY(m_sunDirection, rotationIncrement);
   }

   if (key == 51) //3
   {
      m_terrain->Transform(glm::rotate(glm::mat4(), -rotationIncrement, glm::vec3(1, 0, 0)));
   }

   if (key == 52) //4
   {
      m_terrain->Transform(glm::rotate(glm::mat4(), rotationIncrement, glm::vec3(1, 0, 0)));
   }

   std::cout << glm::to_string(m_sunDirection) << std::endl;
}



void Application::UpdateViewMatrix()
{
   auto up = glm::vec3(0, 1, 0);
   m_view = glm::lookAt(m_eyePosition, glm::vec3(0, 0, 0) - m_eyePosition, up);
}