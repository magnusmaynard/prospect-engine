#pragma once
#include "IApplication.h"
#include "Window.h"
#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>

class Application : public IApplication
{
public:
   Application();

   void Startup() override;
   void Shutdown() override;
   void Render(const double time) override;

private:
   Window m_window;
   std::unique_ptr<ShaderProgram> m_skyboxShader;
   std::unique_ptr<ShaderProgram> m_terrainShader;

   GLint m_skyboxTimeLocation = 0;
   GLint m_skyboxViewLocation = 0;
   GLint m_skyboxProjectionLocation = 0;
   GLint m_skyboxResolutionLocation = 0;
   GLint m_terrainViewLocation = 0;
   GLint m_terrainProjectionLocation = 0;

   glm::mat4 m_view;
   glm::mat4 m_projection;

   glm::vec4 m_backgroundColor = { 0.0, 0.0, 0.0, 1.0 };
};
