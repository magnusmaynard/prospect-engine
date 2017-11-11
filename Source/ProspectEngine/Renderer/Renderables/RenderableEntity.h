#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Scene/Entity_impl.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   struct GlobalUniformBuffers;
   class Camera_impl;
   class Scene_impl;
   class VertexData;

   class RenderableEntity : public IRenderable
   {
   public:
      RenderableEntity(
         const GlobalUniformBuffers& globalUniformBuffers,
         Entity_impl& entity,
         VertexData& vertexData);
      ~RenderableEntity();

      RenderableEntity(const RenderableEntity& other) = delete;
      RenderableEntity& operator=(const RenderableEntity &) = delete;
      RenderableEntity(RenderableEntity&& other);
      RenderableEntity& operator=(RenderableEntity&& other) = delete;

      void Render() override;

   private:
      void BindTransform(const glm::mat4& transform);
      void BindMaterial(const Material& material);

      Entity_impl& m_entity;

      UniformBuffer<MaterialUniforms> m_materialUniformBuffer;
      VertexData& m_vertexData;

      Shader& m_shader;
   };
}
