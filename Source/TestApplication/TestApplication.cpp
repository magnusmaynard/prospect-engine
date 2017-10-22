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

using namespace glm;

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

   m_scene.GetCamera().LookAt(vec3(0, 10, 50), vec3(0, 0, 0));

   Bitmap heightMap = IO::ReadBitmap(IO::GetExecutablePath() + "TerrainMaps\\bagstone2.bmp");

   m_scene.CreateTerrain(
      vec3(),
      heightMap,
      800,
      0,
      50);


   //m_scene.CreateAtmosphere();

   //Material& grass = m_materialLib.CreateMaterial(Color(0.1f, 0.6f, 0.1f));
   //Material& matRed = m_materialLib.CreateMaterial(Color(1, 0.2f, 0.2f));
   //Material& maGrey = m_materialLib.CreateMaterial(Color(0.5f, 0.5f, 0.5f));

   //Mesh& groundPlane = m_meshLib.CreatePlane(vec2(100, 100));
   //Mesh& testPlane = m_meshLib.CreatePlane(vec2(10, 10));

   //auto& ground = m_scene.AddEntity(&groundPlane, &grass);
   //ground.SetRotation(vec3(0, 45, 0));
   //ground.SetTranslation(vec3(0, 10, 0));

   //Entity& child = ground.AddEntity(&testPlane, &matRed);
   //Entity& child2 = child.AddEntity(&testPlane, &maGrey);
}

void TestApplication::OnUpdate(double timeElapsed)
{
   static float counter = 0;
   counter += 0.1f;

   //Apply direction.
   m_playerMomentum += m_playerDirection * m_playerSpeed * static_cast<float>(timeElapsed);

   //Apply friction.
   if (length(m_playerMomentum) > m_playerThreshold)
   {
      auto& camera = m_scene.GetCamera();
      camera.SetPosition(camera.GetPosition() + m_playerMomentum);
      m_playerMomentum *= 1.0 - m_playerFriction;
   }

   //auto& e1 = m_scene.GetEntity(0).GetEntity(0);
   //e1.SetTranslation(vec3(-5, 10, -20));
   //e1.SetRotation(vec3(0, counter * 10.0, 0));

   //auto& e2 = m_scene.GetEntity(0).GetEntity(0).GetEntity(0);
   //e2.SetTranslation(vec3(-5, 10, -40));
   //e2.SetRotation(vec3(0, counter * 10.0, 0));
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
         //m_scene.GetLight()[0].SetDirection();
         break;
      }
      case Key::D4:
      {
         //m_scene.GetLight()[0].SetDirection();
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
      default:
      {
         break;
      }
   }

   UpdatePlayerDirection();
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
      default:
      {
         break;
      }
   }

   UpdatePlayerDirection();
}

void TestApplication::OnMouseMove(const glm::vec2& oldPosition, const glm::vec2& newPosition)
{
}

void TestApplication::OnShutdown()
{
}

void TestApplication::UpdatePlayerDirection()
{
   vec3 playerDirection;

   if (m_playerForward)
   {
      playerDirection += m_scene.GetCamera().GetForward();
   }
   if (m_playerBackward)
   {
      playerDirection -= m_scene.GetCamera().GetForward();
   }
   if (m_playerLeft)
   {
      playerDirection += m_scene.GetCamera().GetLeft();
   }
   if (m_playerRight)
   {
      playerDirection -= m_scene.GetCamera().GetLeft();
   }

   if (length(playerDirection) > m_playerThreshold)
   {
      m_playerDirection = normalize(playerDirection);
   }
   else
   {
      m_playerDirection = vec3();
   }
}
