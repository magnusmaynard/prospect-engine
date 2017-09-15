#include "TestApplication.h"

#include <iostream>
#include "Key.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Color.h"
#include "MeshLibrary.h"
#include "MaterialLibrary.h"
#include "Camera.h"

using namespace glm;

TestApplication::TestApplication()
   :
   m_engine(*this, 600, 400),
   m_scene(m_engine.GetScene()),
   m_meshLib(m_engine.GetMeshLibrary()),
   m_materialLib(m_engine.GetMaterialLibrary())
{
   m_engine.Start();
}

void TestApplication::OnStartup()
{
   m_engine.SetTitle("Test Application");

   m_scene.GetCamera().LookAt(vec3(0, 100, 100), vec3(0, 0, 0));

   Mesh& groundPlane = m_meshLib.CreatePlane(vec2(100, 100));
   Material& grass = m_materialLib.CreateMaterial(Color(0.1, 0.6, 0.1));
   m_scene.CreateEntity(groundPlane, grass);

   Mesh& testPlane = m_meshLib.CreatePlane(vec2(10, 10));

   Material& matRed = m_materialLib.CreateMaterial(Color(1, 0.2, 0.2));
   Entity& test1 = m_scene.CreateEntity(testPlane, matRed);
   test1.SetRotation(vec3(90, 0, 0));

   Material& matBlue = m_materialLib.CreateMaterial(Color(0.2, 0.2, 1));
   Entity& test2 = m_scene.CreateEntity(testPlane, matBlue);
   test2.SetRotation(vec3(90, 0, 90));
}

void TestApplication::OnUpdate(const unsigned int time)
{
   static float counter = 0;
   counter += 0.1;

   auto& e1 = m_scene.GetEntityAtIndex(1);
   e1.SetTranslation(vec3(-10, 0, -50));
   e1.SetRotation(vec3(cos(counter), 0, sin(counter)));

   auto& e2 = m_scene.GetEntityAtIndex(2);
   e2.SetTranslation(vec3(sin(counter) * 50, 0, cos(counter) * 50));
}

void TestApplication::OnKeyDown(const Key& key, const KeyModifier& modifier)
{
   float moveIncrement = 10.0;

   switch (key)
   {
      case Key::Escape:
      {
         m_engine.Close();
         break;
      }
      case Key::W:
      {
         auto& camera = m_scene.GetCamera();
         vec3 position = camera.GetPosition() + camera.GetForwardDirection() * moveIncrement;
         camera.SetPosition(position);
         break;
      }
      case Key::S:
      {
         auto& camera = m_scene.GetCamera();
         vec3 position = camera.GetPosition() - camera.GetForwardDirection() * moveIncrement;
         camera.SetPosition(position);
         break;
      }
      default:
      {
         break;
      }
   }
}

void TestApplication::OnKeyUp(const Key& key, const KeyModifier& modifier)
{
}


void TestApplication::OnShutdown()
{
}
