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
#include "Lights/Light.h"
#include "Terrain.h"
#include <iostream>
#include <glm/gtx/rotate_vector.inl>

using namespace glm;
using namespace Prospect;

TestApplication::TestApplication()
   :
   m_engine(*this, 1280, 720),
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

   m_scene.GetCamera().LookAt({ 0, 40, 80 }, { 0, 10, 0 });

   const Bitmap heightMap = IO::ReadBitmap(IO::GetExecutablePath() + "TerrainMaps\\noise.bmp");

   //Terrain terrain(vec3(), heightMap, 800, 0, 100);
   //m_scene.SetTerrain(terrain);

   //Atmosphere atmosphere;
   //m_scene.SetAtmosphere(atmosphere);
   //atmosphere.SetAltitude(1505);

   Light light1(vec3(0, 0, 0), vec3(0, -1, 0));
   m_scene.AddLight(light1);

   Light light2(vec3(0, 0, 0), vec3(1, 0, 0));
   m_scene.AddLight(light2);

   Material blue = m_materialLib.CreateMaterial({0.1f, 0.8f, 0.1f}, {0.1f, 0.1f, 0.1f}, { 1, 1, 1}, 100);
   Material red = m_materialLib.CreateMaterial(Color::Red());
   Material gray = m_materialLib.CreateMaterial(Color::Black());

   Mesh plane = m_meshLib.CreatePlane({ 20, 20 }, { 10, 10 });
   Mesh largePlane = m_meshLib.CreatePlane({ 200, 200 }, { 10, 10 });
   Mesh cube = m_meshLib.CreateCube({ 10, 10, 10 });

   Entity e0(plane, blue);
   e0.SetTranslation({ 0, 20, 0 });
   m_scene.AddEntity(e0);

   Entity e1(plane, red);
   e1.SetTranslation({ 60, 0, 0 });
   e1.SetScale({ 0.4, 0.4, 0.4 });
   e0.AddEntity(e1);

   Entity e2(cube, red);
   e2.SetTranslation({ 0, 30, 0 });
   m_scene.AddEntity(e2);

   Entity e3(largePlane, gray);
   m_scene.AddEntity(e3);
}

void TestApplication::OnUpdate(const double timeElapsed)
{
   static float counter = 0;
   counter += 0.1f;

   Camera& camera = m_scene.GetCamera();

   //Update direction.
   vec3 playerDirection;
   if (m_playerForward)
   {
      playerDirection += camera.GetForward();
   }
   if (m_playerBackward)
   {
      playerDirection -= camera.GetForward();
   }
   if (m_playerLeft)
   {
      playerDirection += camera.GetLeft();
   }
   if (m_playerRight)
   {
      playerDirection -= camera.GetLeft();
   }
   if (m_playerUp)
   {
      playerDirection += cross(camera.GetForward(), camera.GetLeft());
   }
   if (m_playerDown)
   {
      playerDirection -= cross(camera.GetForward(), camera.GetLeft());
   }

   if (length(playerDirection) > m_playerThreshold)
   {
      playerDirection = normalize(playerDirection);
   }
   else
   {
      playerDirection = vec3();
   }

   //Apply direction.
   m_playerMomentum += playerDirection * m_playerSpeed * static_cast<float>(timeElapsed);

   //Apply friction.
   if (length(m_playerMomentum) > m_playerThreshold)
   {
      camera.SetPosition(camera.GetPosition() + m_playerMomentum);
      m_playerMomentum *= 1.0 - m_playerFriction;
   }

   auto e0 = m_scene.GetEntity(0);
   e0.SetRotation({ 0, counter * 20.0, 0 });
   
   auto e1 = e0.GetEntity(0);
   e1.SetRotation({ 0, counter * 10.0, 0 });

   auto cube = m_scene.GetEntity(1);
   cube.SetRotation({ counter * 8.0, -counter * 5.0, counter * 3.0 });
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
            atmosphere->SetSunDirection(rotateX(atmosphere->GetSunDirection(), 0.1f));
         }
         break;
      }
      case Key::D4:
      {
         if (auto atmosphere = m_scene.GetAtmosphere())
         {
            atmosphere->SetSunDirection(rotateX(atmosphere->GetSunDirection(), -0.1f));
         }
         break;
      }
      case Key::W:
      {
         m_playerForward = true;
         break;
      }
      case Key::S:
      {
         m_playerBackward = true;
         break;
      }
      case Key::A:
      {
         m_playerLeft = true;
         break;
      }
      case Key::D:
      {
         m_playerRight = true;
         break;
      }
      case Key::C:
      {
         m_playerDown = true;
         break;
      }
      case Key::Space:
      {
         m_playerUp = true;
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
   switch (key)
   {
      case Key::W:
      {
         m_playerForward = false;
         break;
      }
      case Key::S:
      {
         m_playerBackward = false;
         break;
      }
      case Key::A:
      {
         m_playerLeft = false;
         break;
      }
      case Key::D:
      {
         m_playerRight = false;
         break;
      }
      case Key::C:
      {
         m_playerDown = false;
         break;
      }
      case Key::Space:
      {
         m_playerUp = false;
         break;
      }
      default:
      {
         break;
      }
   }
}

void TestApplication::OnMouseMove(const glm::vec2& oldPosition, const glm::vec2& newPosition)
{
}

void TestApplication::OnShutdown()
{
}
