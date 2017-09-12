#include "TestApplication.h"

#include "Key.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Color.h"
#include <iostream>
#include "MeshLibrary.h"

using namespace glm;

TestApplication::TestApplication()
   :
   m_engine(*this, 600, 400),
   m_scene(m_engine.GetScene()),
   m_meshLib(m_engine.GetMeshLibrary())
{
   m_engine.Start();
}

void TestApplication::OnStartup()
{
   m_engine.SetTitle("Test Application");

   //Entity& box0 = m_scene.AddEntity();
   //box0.SetMesh(Mesh::CreatePlane(vec2(15, 15)));
   //box0.SetMaterial(Material(Color(1, 0, 0)));

   //Entity& box1 = m_scene.AddEntity();
   //box1.SetMesh(Mesh::CreatePlane(vec2(10, 10)));
   //box1.SetMaterial(Material(Color(0, 1, 0)));

   //Entity& box2 = m_scene.AddEntity();
   //box2.SetMesh(Mesh::CreatePlane(vec2(10, 10)));
   //box2.SetMaterial(Material(Color(0, 0, 1)));

   //TODO: Use libs to create material and meshs.
   //This means shaders/can be reused on similar material/mesh combinations.

   Mesh& mesh = m_meshLib.CreatePlane(vec2(10, 10));

   Material mat = Material(Color(0, 0, 1));
   Entity& entity = m_scene.CreateEntity(mesh, mat);

   Material mat2 = Material(Color(0, 1, 0));
   Entity& entity2 = m_scene.CreateEntity(mesh, mat2);

   Material mat3 = Material(Color(1, 0, 0));
   Entity& entity3 = m_scene.CreateEntity(mesh, mat3);

   //scene.CreateTerrain();
}

void TestApplication::OnUpdate(const unsigned int time)
{
   static float counter = 0;
   counter += 0.1;

   auto& e0 = m_scene.GetEntityAtIndex(0);
   e0.SetTranslation(vec3(cos(counter), sin(counter), -50));

   auto& e1 = m_scene.GetEntityAtIndex(1);
   e1.SetTranslation(vec3(-10, 0, -50));
   e1.SetRotation(vec3(cos(counter), 0, sin(counter)));

   auto& e2 = m_scene.GetEntityAtIndex(2);
   e2.SetTranslation(vec3(10, 0, -50));
   e2.SetRotation(vec3(0, 0, 45));
   e2.SetScale(vec3(cos(counter), sin(counter), 0));
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
