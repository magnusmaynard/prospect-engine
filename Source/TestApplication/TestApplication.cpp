#include "TestApplication.h"

#include "Key.h"
#include "PolygonMode.h"

TestApplication::TestApplication()
   :
   m_engine(*this, 600, 400)
{
   m_engine.Start();
}

void TestApplication::OnStartup()
{
   m_engine.SetTitle("Test Application");

   Scene& scene = m_engine.GetScene();

   scene.CreateTerrain();
}

void TestApplication::OnUpdate(const unsigned int time)
{
   //m_engine.GetScene().GetCamera().LookAt(vec3(0, 0, 1 + sin(time * 0.01)), vec3(0, 0, 0));
}

void TestApplication::OnKeyDown(const Key& key, const KeyModifier& modifier)
{
   if(key == Key::Escape)
   {
      m_engine.Close();
   }
}

void TestApplication::OnShutdown()
{
}
