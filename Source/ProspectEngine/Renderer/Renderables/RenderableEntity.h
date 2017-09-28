#pragma once
#include "Renderer/Shaders/ShaderProgram.h"
#include "Scene/Entity_impl.h"
#include "RenderableMesh.h"
#include "RenderableMaterial.h"
#include "Renderer/IRenderable.h"

namespace Prospect
{
   class Camera_impl;
   class Scene_impl;
   class UniformBuffer;

   class RenderableEntity : public IRenderable
   {
   public:
      RenderableEntity(Entity_impl& entity, RenderableMesh& renderableMesh);
      ~RenderableEntity();
      RenderableEntity(const RenderableEntity& other) = delete;
      RenderableEntity& operator=(const RenderableEntity &) = delete;
      RenderableEntity(RenderableEntity&& other);
      RenderableEntity& operator=(RenderableEntity&& other) = delete;

      void Render(UniformBuffer& uniformBuffer) override;

   private:
      void BindTransform(const glm::mat4& transform);
      void BindMaterial(const Material& material);

      Entity_impl& m_entity;

      RenderableMesh& m_renderableMesh;

      ShaderProgram m_program;
   };
}
