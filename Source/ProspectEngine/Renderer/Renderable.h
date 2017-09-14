#pragma once
#include "Shaders/ShaderProgram.h"
#include "Scene/Entity_impl.h"
#include "RenderableMesh.h"
#include "RenderableMaterial.h"

namespace Prospect
{
   class Camera_impl;
   class Scene_impl;

   class Renderable
   {
   public:
      Renderable(
         Entity_impl& entity,
         RenderableMesh& renderableMesh,
         RenderableMaterial& renderableMaterial);
      ~Renderable();
      Renderable(const Renderable& other) = delete;
      Renderable& operator=(const Renderable &) = delete;
      Renderable(Renderable&& other);
      Renderable& operator=(Renderable&& other) = delete;

      void Render(Scene_impl& scene);

   private:
      void UseCamera(const Camera_impl& camera);
      void UseTransform(const glm::mat4& transform);

      Entity_impl& m_entity;

      RenderableMesh& m_renderableMesh;
      RenderableMaterial& m_renderableMaterial;

      ShaderProgram m_program;
   };
}
