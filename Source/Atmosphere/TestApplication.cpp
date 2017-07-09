#include "TestApplication.h"

TestApplication::TestApplication():
   m_pe(600, 400)
{
   m_pe.SetStartup(std::bind(&TestApplication::Startup, this));
   m_pe.SetUpdate(std::bind(&TestApplication::Update, this, -1));
   m_pe.SetKeyDown(std::bind(&TestApplication::KeyDown, this, Keys::None));
   m_pe.SetShutdown(std::bind(&TestApplication::Shutdown, this));

   m_pe.Start();
}

void TestApplication::Startup()
{
   m_pe.SetPolygonMode(PolygonMode::Line);

   Scene& scene = m_pe.GetScene();

   scene.CreateTerrain();
}

void TestApplication::Update(unsigned int time)
{
   m_pe.GetScene().GetCamera().LookAt(glm::vec3(0, 0, 1 + sin(time * 0.01)), glm::vec3(0, 0, 0));
}

void TestApplication::KeyDown(const Keys& keys)
{
}

void TestApplication::Shutdown()
{
}
