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
   m_engine.ShowFPS(true);

   m_scene.GetCamera().LookAt(vec3(0, 50, 100), vec3(0, 0, 0));

   Material& grass = m_materialLib.CreateMaterial(Color(0.1f, 0.6f, 0.1f));
   Material& matRed = m_materialLib.CreateMaterial(Color(1, 0.2f, 0.2f));
   Material& matBlue = m_materialLib.CreateMaterial(Color(0.2f, 0.2f, 1));

   Mesh& groundPlane = m_meshLib.CreatePlane(vec2(100, 100));
   Mesh& testPlane = m_meshLib.CreatePlane(vec2(10, 10));

   auto& ground = m_scene.AddEntity(&groundPlane, &grass);
   ground.SetRotation(vec3(0, 45, 0));

   Entity& child = ground.AddEntity(&testPlane, &matRed);
   Entity& child2 = child.AddEntity(&testPlane, &matBlue);
}

void TestApplication::OnUpdate(double timeElapsed)
{
   static float counter = 0;
   counter += 0.1f;

   auto& e1 = m_scene.GetEntity(0).GetEntity(0);
   e1.SetTranslation(vec3(-5, 10, -20));
   e1.SetRotation(vec3(0, counter * 10.0, 0));

   auto& e2 = m_scene.GetEntity(0).GetEntity(0).GetEntity(0);
   e2.SetTranslation(vec3(-5, 10, -40));
   e2.SetRotation(vec3(0, counter * 10.0, 0));
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
         vec3 position = camera.GetPosition() + camera.GetForward() * moveIncrement;
         camera.SetPosition(position);
         break;
      }
      case Key::S:
      {
         auto& camera = m_scene.GetCamera();
         vec3 position = camera.GetPosition() - camera.GetForward() * moveIncrement;
         camera.SetPosition(position);
         break;
      }
      case Key::A:
      {
         auto& camera = m_scene.GetCamera();
         vec3 position = camera.GetPosition() - camera.GetLeft() * moveIncrement;
         camera.SetPosition(position);
         break;
      }
      case Key::D:
      {
         auto& camera = m_scene.GetCamera();
         vec3 position = camera.GetPosition() + camera.GetLeft() * moveIncrement;
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

void TestApplication::OnMouseMove(const glm::vec2& oldPosition, const glm::vec2& newPosition)
{
}

void TestApplication::OnShutdown()
{
}
