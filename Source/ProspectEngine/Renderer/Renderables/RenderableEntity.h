#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Scene/Entity_impl.h"
#include "Renderer/IRenderable.h"

namespace Prospect
{
   class Camera_impl;
   class Scene_impl;
   class UniformBuffer;
   class VertexData;

   class RenderableEntity : public IRenderable
   {
   public:
      RenderableEntity(Entity_impl& entity, VertexData& vertexData);
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

      VertexData& m_vertexData;

      Shader& m_shader;
   };
}
