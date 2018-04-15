#include "ProspectEngine_pch.h"

#include "Renderer.h"
#include "Scene/Mesh_impl.h"
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Lights/ILight_impl.h"
#include "Renderer/Debugger/Debug.h"
#include "Libraries/MaterialLibrary_impl.h"
#include "Renderer/Shadows/ShadowMap.h"
#include "Scene2D/Scene2D_impl.h"

using namespace Prospect;
using namespace glm;

Renderer::Renderer(const MaterialLibrary_impl& materialLibrary, const ivec2& size)
   :
   m_showWireframe(false),
   m_shaderLibrary(m_globalUniformBuffers),
   m_materialLibrary(materialLibrary),
   m_gBuffer(size),
   m_entityRenderer(m_shaderLibrary),
   m_terrainRenderer(m_shaderLibrary),
   m_atmosphereRenderer(m_shaderLibrary),
   m_sunRenderer(m_shaderLibrary),
   m_textRenderer(m_shaderLibrary),
   m_lightingRenderer(m_shaderLibrary)
{
   Initialise();
}

void Renderer::Initialise()
{
#ifdef _DEBUG
   glEnable(GL_DEBUG_OUTPUT);
#endif

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   glEnable(GL_BLEND);

   glEnable(GL_CULL_FACE);
   glFrontFace(GL_CCW);

   glClearColor(1, 1, 1, 1);

   //glCreateFramebuffers(1, &m_screenshotFBO);
   //glBindFramebuffer(GL_FRAMEBUFFER, m_screenshotFBO);

   //glNamedFramebufferDrawBuffer(m_screenshotFBO, GL_BACK);
   //glNamedFramebufferReadBuffer(m_screenshotFBO, GL_BACK);
   //const GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   //if (error != GL_FRAMEBUFFER_COMPLETE)
   //{
   //   std::cerr << "Error: Failed to create framebuffer: " << std::hex << error << std::endl;
   //}

   Debug::Points::Initialise(m_shaderLibrary);
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

   glEnable(GL_DEPTH_TEST);
}

void Renderer::Render(const double time, Scene_impl& scene, Scene2D_impl& scene2D)
{
   UpdateState();
   UpdateGlobalUniformBuffers(scene);

   Clear();
   m_gBuffer.Clear();

   //ShadowPass(scene);
   GeometryPass(scene);
   //LightingPass();
   //EffectsPass(scene, scene2D);

   Debug::CheckErrors();
}

void Renderer::ShadowPass(Scene_impl& scene)
{
   m_shadowMaps.Update(scene);

   for (int i = 0; i < m_shadowMaps.Count(); i++)
   {
      m_shadowMaps.Bind(i);
      m_shadowMaps.Clear();

      //Update camera to lights perspective.
      CameraUniforms camera;
      camera.PerspectiveProjection = m_shadowMaps.GetProjectionMatrix(i);
      camera.View = m_shadowMaps.GetViewMatrix(i);
      m_globalUniformBuffers.Camera.Update(camera);

      //Render scene.
      RenderEntities(scene.GetRootEntityImpl());

      if (auto* terrain = scene.GetTerrainImpl())
      {
         m_terrainRenderer.Render(*terrain);
      }
   }

   //Reset camera back to normal.
   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));
}

void Renderer::GeometryPass(Scene_impl& scene)
{
   BindDefaultFramebuffer();
   //m_gBuffer.Bind();

   RenderEntities(scene.GetRootEntityImpl());

   //if(auto* terrain = scene.GetTerrainImpl())
   //{
   //   m_terrainRenderer.Render(*terrain);
   //}

   //if (auto* atmosphere = scene.GetAtmosphereImpl())
   //{
   //   m_sunRenderer.Render(*atmosphere);
   //}

   //Debug::Points::Render();
}

void Renderer::LightingPass()
{
   BindDefaultFramebuffer();

   m_lightingRenderer.Render(m_gBuffer, m_shadowMaps);
}

void Renderer::EffectsPass(Scene_impl& scene, Scene2D_impl& scene2D)
{
   BindDefaultFramebuffer();

   if (auto* atmosphere = scene.GetAtmosphereImpl())
   {
      m_atmosphereRenderer.Render(*atmosphere, m_gBuffer);
   }

   //TODO: Improve 2d scene rendering, make more generic.
   for (int i = 0; i < scene2D.GetTextCount(); i++)
   {
      m_textRenderer.Render(scene2D.GetTextByIndex(i));
   }
}

void Renderer::RenderEntities(Entity_impl& entity)
{
   m_entityRenderer.Render(entity);

   auto& children = entity.GetChildren();
   for (auto& child : children)
   {
      //TODO: make non-recursive, don't store entities in a graph.
      RenderEntities(*child.get());
   }
}

void Renderer::UpdateGlobalUniformBuffers(const Scene_impl& scene)
{
   const Camera_impl& camera = scene.GetCameraImpl();

   m_globalUniformBuffers.Camera.Update(CameraUniforms(scene.GetCameraImpl()));

   m_globalUniformBuffers.MaterialLibrary.Update(MaterialLibraryUniforms(m_materialLibrary));

   std::vector<const DirectionalLight_impl*> directionalLights;

   for(int i = 0; i < scene.GetLightCount(); i++)
   {
      const ILight_impl* light = scene.GetLightImpl(i);

      switch (light->GetType())
      {
      case LightType::Directional:
         directionalLights.push_back(static_cast<const DirectionalLight_impl*>(light));
         break;
      case LightType::Spot:
      case LightType::Point:
      default:
         //Do nothing.
         break;
      }
   }

   m_globalUniformBuffers.DirectionalLights.Update(DirectionalLightListUniforms(directionalLights));
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

void Renderer::BindDefaultFramebuffer()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glViewport(0, 0, m_size.x, m_size.y);
}

void Renderer::ShowWireframe(const bool showWireframe)
{
   m_showWireframe = showWireframe;
}

void Renderer::Resize(const ivec2& size)
{
   m_size = size;
   m_gBuffer.Resize(size);
}

const Image Renderer::Screenshot(Scene_impl& scene)
{
   //glBindFramebuffer(GL_FRAMEBUFFER, m_screenshotFBO);
   glViewport(0, 0, m_size.x, m_size.y);
   glClearColor(0, 0, 0, 0);
   Clear();

   //Render scene.
   RenderEntities(scene.GetRootEntityImpl());

   std::vector<unsigned char> data;
   data.resize(m_size.x * m_size.y * 4);
   glReadPixels(0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);


   std::vector<unsigned char> processedData;
   processedData.resize(m_size.x * m_size.y * 4);
   for (int y = 0; y < m_size.y; y++)
   {
      const int currentRow = y * m_size.x * 4;
      const int oppositeRow = (m_size.y - 1) * m_size.x * 4 - currentRow;

      for (int x = 0; x < m_size.x * 4; x+=4)
      {
         const int oppositeColumn = oppositeRow + x;
         const int currentColumn = currentRow + x;

         float r = static_cast<float>(data[currentColumn + 0]) / 255.f;
         float g = static_cast<float>(data[currentColumn + 1]) / 255.f;
         float b = static_cast<float>(data[currentColumn + 2]) / 255.f;
         float a = static_cast<float>(data[currentColumn + 3]) / 255.f;

         r /= a;
         g /= a;
         b /= a;
         
         processedData[oppositeColumn + 0] = static_cast<unsigned char>(r * 255.f);
         processedData[oppositeColumn + 1] = static_cast<unsigned char>(g * 255.f);
         processedData[oppositeColumn + 2] = static_cast<unsigned char>(b * 255.f);
         processedData[oppositeColumn + 3] = static_cast<unsigned char>(a * 255.f);
      }
   }

   //flippedData[oppositeColumn + 0] = data[currentRow + 0];
   //flippedData[oppositeColumn + 1] = data[currentRow + 1];
   //flippedData[oppositeColumn + 2] = data[currentRow + 2];
   //flippedData[oppositeColumn + 3] = data[currentRow + 3];

   Image image(m_size.x, m_size.y, 4, processedData);

   Debug::CheckErrors();


   glClearColor(1, 1, 1, 1);//Restore clear color.

   return image;
}
