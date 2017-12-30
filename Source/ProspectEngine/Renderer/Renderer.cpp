#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/Light_impl.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Renderer/Debugger/Debug.h"
#include "Libraries/MaterialLibrary_impl.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer(const MaterialLibrary_impl& materialLibrary, const ivec2& size)
   :
   m_showFPS(false),
   m_showWireframe(false),
   m_frameCount(0),
   m_previousTime(0),
   m_shaderLibrary(m_globalUniformBuffers),
   m_materialLibrary(materialLibrary),
   m_gBuffer(m_shaderLibrary, size)
{
   Initialize();
}

void Renderer::Initialize()
{
#ifdef _DEBUG
   glEnable(GL_DEBUG_OUTPUT);
#endif

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   glEnable(GL_BLEND);

   glEnable(GL_CULL_FACE);
   glFrontFace(GL_CCW);

   m_fpsText = std::make_unique<RenderableText>(m_shaderLibrary, "", ivec2(4, 0), 12);
}

void Renderer::UpdateState()
{
   if (m_showWireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }
   else
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }
}

void Renderer::Render(const double time, Scene_impl& scene)
{
   UpdateState();

   Clear();
   m_gBuffer.Clear();

   //Update
   UpdateGlobalUniformBuffers(scene);
   UpdateRenderableEntity(scene.GetRootEntityImpl());
   //UpdateRenderableTerrain(scene);
   //UpdateRenderableAtmosphere(scene);

   //Geometry pass
   m_gBuffer.Bind();

   glEnable(GL_DEPTH_TEST);

   for (auto& renderable : m_renderables)
   {
      renderable->Render();
   }

   //Lighting pass
   m_gBuffer.Present();

   //if (m_terrain)
   //{
   //   m_terrain->Render();
   //}

   ////Atmosphere
   //m_depthTexture.Update();

   //if (m_atmosphere)
   //{
   //   m_atmosphere->Render();
   //}

   //ClearDepthBuffer();

   ////HUD
   //if (m_showFPS)
   //{
   //   UpdateFPS(time);
   //   m_fpsText->Render();
   //}

   Debug::CheckErrors();
}


void Renderer::UpdateRenderableEntity(Entity_impl& entity)
{
   if (entity.ChildEntityAdded())
   {
      if (entity.GetRenderable() == nullptr &&
         entity.GetMeshImpl() != nullptr &&
         entity.GetMaterialImpl() != nullptr)
      {
         VertexData& vertexData = GetVertexData(*entity.GetMeshImpl());

         m_renderables.push_back(std::make_unique<RenderableEntity>(m_shaderLibrary, entity, vertexData));

         entity.SetRenderable(m_renderables.back().get());
      }

      auto& children = entity.GetChildren();
      for (auto& child : children)
      {
         UpdateRenderableEntity(*child.get());
      }

      entity.ResetChildEntityAdded();
   }
}

VertexData& Renderer::GetVertexData(Mesh_impl& mesh)
{
   auto itr = m_vertexDataMap.find(mesh.GetID());
   if (itr == m_vertexDataMap.end())
   {
      return m_vertexDataMap.emplace(mesh.GetID(), VertexData(mesh)).first->second;
   }
   
   return itr->second;
}

void Renderer::UpdateGlobalUniformBuffers(const Scene_impl& scene)
{
   const Camera_impl& camera = scene.GetCameraImpl();

   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));

   m_globalUniformBuffers.MaterialLibrary.Update(MaterialLibraryUniforms(m_materialLibrary));

   std::vector<const Light_impl*> lights;

   //Atmosphere lights.
   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      lights.push_back(&atmosphere->GetLightImpl());
   }

   //Scene lights.
   for(int i = 0; i < scene.GetLightCount(); i++)
   {
      lights.push_back(scene.GetLightImpl(i));
   }

   m_globalUniformBuffers.Lights.Update(LightsUniforms(lights));
}

void Renderer::UpdateRenderableTerrain(const Scene_impl& scene)
{
   if(m_terrain == nullptr)
   {
      const Terrain_impl* terrain = scene.GetTerrainImpl();
      if (terrain)
      {
         m_terrain = std::make_unique<RenderableTerrain>(m_shaderLibrary, *terrain);
      }
   }
}

void Renderer::UpdateRenderableAtmosphere(const Scene_impl& scene)
{
   if (m_atmosphere == nullptr)
   {
      if (const auto atmosphere = scene.GetAtmosphereImpl())
      {
         m_atmosphere = std::make_unique<RenderableAtmosphere>(m_shaderLibrary, m_depthTexture, *atmosphere);

         atmosphere->SetRenderable(m_atmosphere.get());
      }
   }
}

void Renderer::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   ClearDepthBuffer();
}

void Renderer::ClearDepthBuffer()
{
   glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::ShowFPS(const bool showFPS)
{
   m_showFPS = showFPS;
}

void Renderer::ShowWireframe(const bool showWireframe)
{
   m_showWireframe = showWireframe;
}

void Renderer::Resize(const ivec2& size)
{
   m_depthTexture.Resize(size);
   m_gBuffer.Resize(size);
}

void Renderer::UpdateFPS(const double time)
{
   static const double FPS_INTERVAL = 1000.0;

   m_frameCount++;

   if (time - m_previousTime >= FPS_INTERVAL)
   {
      const std::string text = std::to_string(m_frameCount);

      m_fpsText->SetText(text);

      m_frameCount = 0;
      m_previousTime = time;
   }
}

