#pragma once
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Scene/Entity_impl.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Pipeline/Shaders/BlinnShader.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;
   class Camera_impl;
   class Scene_impl;
   class VertexData;

   class RenderableEntity : public IRenderable
   {
   public:
      RenderableEntity(
         ShaderLibrary& shaderLibrary,
         Entity_impl& entity,
         VertexData& vertexData);
      ~RenderableEntity();

      RenderableEntity(const RenderableEntity& other) = delete;
      RenderableEntity& operator=(const RenderableEntity &) = delete;
      RenderableEntity(RenderableEntity&& other);
      RenderableEntity& operator=(RenderableEntity&& other) = delete;

      void Render() override;
      void MakeDirty() override;

   private:
      Entity_impl& m_entity;

      VertexData& m_vertexData;
      BlinnShader& m_shader;
   };
}
