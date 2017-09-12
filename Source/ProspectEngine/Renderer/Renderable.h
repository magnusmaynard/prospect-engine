#pragma once
#include "Shaders/ShaderProgram.h"
#include "RendererDefines.h"
#include "Scene/Entity_impl.h"
#include "RenderableMesh.h"

namespace Prospect
{
   class Camera;
   class Scene_impl;

   class Renderable
   {
   public:
      Renderable(Entity_impl& entity, RenderableMesh& renderableMesh);
      ~Renderable();
      Renderable(const Renderable& other) = delete;
      Renderable& operator=(const Renderable &) = delete;
      Renderable(Renderable&& other);
      Renderable& operator=(Renderable&& other) = delete;

      void Render(Scene_impl& scene);

   private:
      void DrawMesh(const Mesh& mesh);
      void UpdateBuffers(const Mesh& mesh);
      void UseCamera(const Camera& camera);
      void UseTransform(const glm::mat4& transform);
      void UseMaterial(const Material& material);

      Entity_impl* m_entity; //TODO: make reference

      RenderableMesh& m_renderableMesh;

      ShaderProgram m_program;
   };
}
