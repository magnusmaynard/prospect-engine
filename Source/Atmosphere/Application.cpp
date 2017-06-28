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
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE); //GL_ONE_MINUS_SRC_ALPHA
   //glEnable(GL_BLEND); //TODO: blend effects the same object drawn over itself. Enable depth test?

   //glCullFace(GL_BACK);
   //glEnable(GL_CULL_FACE);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //View.
   UpdateViewMatrix();

   //Projection.
   float aspect = m_window.GetSize().x / m_window.GetSize().y;
   m_projection = glm::perspective(40.0f, aspect, 0.0001f, 10000.0f); //55

   m_terrain = std::make_unique<Terrain>();
   //m_atmosphere = std::make_unique<Atmosphere>();
   //m_cubeMap = std::make_unique<CubeMap>();

   //test TODO
   //m_terrain->Draw(m_view, m_projection, m_eyePosition);
}

void Application::Shutdown()
{
}

void Application::Render(const double time)
{
   //Clear
   //glClearBufferfv(GL_COLOR, 0, &m_backgroundColor[0]);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //m_eyePosition.x -= sin(time) * 0.06;
   //m_eyePosition.z += sin(time * 2.0) * 0.5;
   UpdateViewMatrix();

   ////Earth
   m_terrain->Draw(m_view, m_projection, m_eyePosition);

   //m_cubeMap->Draw(m_view, m_projection);

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
   const float rotationIncrement = 0.06f;
   const float zoomIncrement = 2.8f;

   if (key == 49) //1
   {
      //m_sunDirection = glm::rotateY(m_sunDirection, -rotationIncrement);

      m_eyePosition += m_eyeDirection * zoomIncrement;
   }

   if (key == 50) //2
   {
      //m_sunDirection = glm::rotateY(m_sunDirection, rotationIncrement);

      m_eyePosition -= m_eyeDirection * zoomIncrement;
   }

   if (key == 51) //3
   {
      m_eyeDirection = glm::rotateX(m_eyeDirection, -rotationIncrement);
      //m_terrain->Transform(glm::rotate(glm::mat4(), -rotationIncrement, glm::vec3(1, 0, 0)));
   }

   if (key == 52) //4
   {
      m_eyeDirection = glm::rotateX(m_eyeDirection, rotationIncrement);
      //m_terrain->Transform(glm::rotate(glm::mat4(), rotationIncrement, glm::vec3(1, 0, 0)));
   }
   if (key == 53) //5
   {
      m_eyePosition.x += zoomIncrement;
   }

   if (key == 54) //6
   {
      m_eyePosition.x -= zoomIncrement;
   }

}

void Application::UpdateViewMatrix()
{
   auto up = glm::vec3(0, 1, 0);
   m_view = glm::lookAt(m_eyePosition, m_eyePosition + m_eyeDirection, up);
}