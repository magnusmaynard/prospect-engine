#include "TestApplication.h"

#include "Key.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Color.h"
#include "MeshLibrary.h"
#include "MaterialLibrary.h"
#include "Camera.h"
#include "Bitmap.h"
#include "Utilities/IO.h"
#include "Atmosphere.h"
#include "Lights/ILight.h"
#include "Lights/LightType.h"
#include "Lights/DirectionalLight.h"
#include "Terrain.h"
#include <iostream>
#include <glm/gtx/rotate_vector.inl>

using namespace glm;
using namespace Prospect;

TestApplication::TestApplication()
   :
   m_engine(*this, { 1280, 720 }),
   m_scene(m_engine.GetScene()),
   m_meshLib(m_engine.GetMeshLibrary()),
   m_materialLib(m_engine.GetMaterialLibrary()),
   m_player(m_scene.GetCamera())
{
   m_engine.Start();
}

void TestApplication::OnStartup()
{
   m_engine.SetTitle("Test Application");
   m_engine.ShowFPS(true);

   m_player.SetPosition({ 0, 30, -40 });

   const Bitmap heightMap = IO::ReadBitmap(IO::GetExecutablePath() + "Textures\\texture_noise.bmp", true);
   const Bitmap grassTexture = IO::ReadBitmap(IO::GetExecutablePath() + "Textures\\texture_grass.bmp");

   Terrain terrain(vec3(), heightMap, 800, 0, 100);
   terrain.SetGroundTexture(grassTexture);
   m_scene.SetTerrain(terrain);

   DirectionalLight sunLight(vec3(0, -1, 1));
   //sunLight.SetShadowCascades(4);
   m_scene.AddLight(sunLight);

   //DirectionalLight otherLight(vec3(1, -1, 0));
   //m_scene.AddLight(otherLight);
   
   Atmosphere atmosphere;
   atmosphere.SetAltitude(1505);
   atmosphere.SetLight(sunLight);
   m_scene.SetAtmosphere(atmosphere);

   Material red = m_materialLib.CreateMaterial(Color::Red());
   Material white = m_materialLib.CreateMaterial(Color::White(), Color::White(), Color::White(), 128);

   //Light light1(vec3(50, 30, 0), vec3(0, -1, 0), LightType::Point);
   //light1.SetRange(200);
   //m_scene.AddLight(light1);

   Mesh turbineBaseMesh = m_meshLib.CreateEmpty();
   IO::ReadObj(turbineBaseMesh, IO::GetExecutablePath() + "Models\\windturbine_smooth_base.obj");
   Entity turbine(turbineBaseMesh, white);

   Mesh turbinePropMesh = m_meshLib.CreateEmpty();
   IO::ReadObj(turbinePropMesh, IO::GetExecutablePath() + "Models\\windturbine_smooth_prop.obj");
   Entity turbineProp(turbinePropMesh, white);

   turbine.AddEntity(turbineProp);
   m_scene.AddEntity(turbine);
   turbine.SetTranslation({ 0, 55, 0 });
   turbine.SetScale({ 2, 2, 2 });

   //Cube
   Mesh plane = m_meshLib.CreatePlane({ 10, 10 });

   Entity e1(plane, white);
   e1.SetTranslation({ 0, -30, 50 });
   m_scene.AddEntity(e1);


   //Cube
   Mesh cube = m_meshLib.CreateCube({ 10, 10, 10 });

   Entity e2(cube, red);
   e2.SetTranslation({ 0, 30, -100 });
   m_scene.AddEntity(e2);
}

void TestApplication::OnUpdate(const double timeElapsed)
{
   static float counter = 0;
   counter += 0.1f;

   m_player.Update(timeElapsed);

   auto turbineProp = m_scene.GetEntity(0).GetEntity(0);
   turbineProp.SetRotation({ 0, 0, counter * 8.0 });
}

void TestApplication::OnKeyDown(const Key& key, const KeyModifier& modifier)
{
   switch (key)
   {
      case Key::Escape:
      {
         m_engine.Close();
         break;
      }
      case Key::D1:
      {
         m_engine.ShowWireframe(false);
         break;
      }
      case Key::D2:
      {
         m_engine.ShowWireframe(true);
         break;
      }
      case Key::D3:
      {
         if (auto atmosphere = m_scene.GetAtmosphere())
         {
            atmosphere->SetSunDirection(rotateX(atmosphere->GetSunDirection(), 0.02f));
         }
         break;
      }
      case Key::D4:
      {
         if (auto atmosphere = m_scene.GetAtmosphere())
         {
            atmosphere->SetSunDirection(rotateX(atmosphere->GetSunDirection(), -0.02f));
         }
         break;
      }
      case Key::W:
      {
         m_player.Move(Direction::Forward);
         break;
      }
      case Key::S:
      {
         m_player.Move(Direction::Backward);
         break;
      }
      case Key::A:
      {
         m_player.Move(Direction::Left);
         break;
      }
      case Key::D:
      {
         m_player.Move(Direction::Right);
         break;
      }
      case Key::C:
      {
         m_player.Move(Direction::Down);
         break;
      }
      case Key::Space:
      {
         m_player.Move(Direction::Up);
         break;
      }
      default:
      {
         break;
      }
   }

   //Update walk mode.
   if(modifier == KeyModifier::Shift)
   {
      m_player.SetWalkMode(WalkMode::Run);
   }
   else if(modifier == KeyModifier::Control)
   {
      m_player.SetWalkMode(WalkMode::Crawl);
   }
   else
   {
      m_player.SetWalkMode(WalkMode::Walk);
   }
}

void TestApplication::OnKeyUp(const Key& key, const KeyModifier& modifier)
{
   switch (key)
   {
      case Key::W:
      {
         m_player.Stop(Direction::Forward);
         break;
      }
      case Key::S:
      {
         m_player.Stop(Direction::Backward);
         break;
      }
      case Key::A:
      {
         m_player.Stop(Direction::Left);
         break;
      }
      case Key::D:
      {
         m_player.Stop(Direction::Right);
         break;
      }
      case Key::C:
      {
         m_player.Stop(Direction::Down);
         break;
      }
      case Key::Space:
      {
         m_player.Stop(Direction::Up);
         break;
      }
      default:
      {
         break;
      }
   }
   //Update walk mode.
   if (modifier == KeyModifier::Shift)
   {
      m_player.SetWalkMode(WalkMode::Run);
   }
   else if (modifier == KeyModifier::Control)
   {
      m_player.SetWalkMode(WalkMode::Crawl);
   }
   else
   {
      m_player.SetWalkMode(WalkMode::Walk);
   }
}

void TestApplication::OnMouseMove(const vec2& oldPosition, const vec2& newPosition)
{
}

void TestApplication::OnShutdown()
{
}
