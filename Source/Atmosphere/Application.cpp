#include "Application.h"

#include <glm/vec4.hpp>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

//TODO: This constructor never gets passed window init because of render loop. Remove it somehow?
Application::Application()
   :
   m_window(this)
{
}

void Application::Startup()
{
   m_skyboxShader = std::make_unique<ShaderProgram>("skybox.vs.glsl", "skybox.fs.glsl");
   m_skyboxTimeLocation = m_skyboxShader->GetUniformLocation("time");
   m_skyboxViewLocation = m_skyboxShader->GetUniformLocation("view");
   m_skyboxProjectionLocation = m_skyboxShader->GetUniformLocation("projection");
   m_skyboxResolutionLocation = m_skyboxShader->GetUniformLocation("resolution");

   m_terrainShader = std::make_unique<ShaderProgram>("terrain.vs.glsl", "terrain.fs.glsl");
   m_terrainViewLocation = m_terrainShader->GetUniformLocation("view");
   m_terrainProjectionLocation = m_terrainShader->GetUniformLocation("projection");

   //View.
   auto position = glm::vec3(0, 0, 0);
   auto front = glm::vec3(0, 0, 1);
   auto up = glm::vec3(0, 1, 0);
   m_view = glm::lookAt(glm::vec3(0, 0, 0), position + front, up);

   //Projection.
   float aspect = m_window.GetSize().x / m_window.GetSize().y;
   m_projection = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
}

void Application::Shutdown()
{
}

void Application::Render(const double time)
{
   //Clear
   glClearBufferfv(GL_COLOR, 0, &m_backgroundColor[0]);

   //Skybox
   m_skyboxShader->Use();

   glUniform1f(m_skyboxTimeLocation, time);
   glUniformMatrix4fv(m_skyboxViewLocation, 1, GL_FALSE, &m_view[0][0]);
   glUniformMatrix4fv(m_skyboxProjectionLocation, 1, GL_FALSE, &m_projection[0][0]);
   glUniform2fv(m_skyboxResolutionLocation, 1, &m_window.GetSize()[0]);

   glDrawArrays(GL_TRIANGLES, 0, 6);

   ////Terrain
   //m_terrainShader->Use();

   //glUniformMatrix4fv(m_terrainViewLocation, 1, GL_FALSE, &m_view[0][0]);
   //glUniformMatrix4fv(m_terrainProjectionLocation, 1, GL_FALSE, &m_projection[0][0]);

   //glDrawArrays(GL_TRIANGLES, 0, 6);

}