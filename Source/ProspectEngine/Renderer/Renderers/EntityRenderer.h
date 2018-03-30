#pragma once
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Scene/Entity_impl.h"
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"
#include "Renderer/Renderers/RenderDataLibrary.h"
#include "Renderer/Renderers/RenderData.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;
   class Camera_impl;
   class Scene_impl;
   class VertexData;

   struct MeshRenderData : RenderData
   {
      GLuint VAO = GL_NULL;

      enum BUFFERS
      {
         BUFFER_VERTICES,
         BUFFER_INDICES,
         BUFFER_NORMALS,
         BUFFER_COUNT,
      };

      GLuint Buffers[BUFFER_COUNT];
   };

   struct EntityRenderData : RenderData
   {
   };

   class EntityRenderer
   {
   public:
      EntityRenderer(ShaderLibrary& shaderLibrary);
      ~EntityRenderer();

      void Render(Entity_impl& entity);

   private:
      static void InitialiseEntity(EntityRenderData& renderData);
      static void DisposeEntity(EntityRenderData& renderData);

      static void InitialiseMesh(MeshRenderData& renderData);
      static void DisposeMesh(MeshRenderData& renderData);

      static void UpdateMesh(MeshRenderData& renderData, const Mesh_impl& mesh);

      BlinnPhongShader& m_shader;

      RenderDataLibrary<EntityRenderData> m_entityRenderDataLibrary;
      RenderDataLibrary<MeshRenderData> m_meshRenderDataLibrary;
   };
}
