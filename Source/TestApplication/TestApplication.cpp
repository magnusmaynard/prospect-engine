#include "TestApplication.h"

#include "Key.h"
#include "PolygonMode.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Color.h"

using namespace glm;


TestApplication::TestApplication()
   :
   m_engine(*this, 600, 400),
   m_scene(m_engine.GetScene())
{
   m_engine.Start();
}

void TestApplication::OnStartup()
{
   m_engine.SetTitle("Test Application");

   Entity& box = m_scene.AddEntity();

   box.SetMesh(Mesh::CreatePlane(vec3(0, 0, 0), vec2(10, 10)));
   box.SetMaterial(Material(Color(1, 0, 0)));

   //scene.CreateTerrain();
}

void TestApplication::OnUpdate(const unsigned int time)
{
   auto& box = m_scene.GetEntity(0);

   box.SetTranslation(vec3(cos(time), sin(time), 0.f));
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
