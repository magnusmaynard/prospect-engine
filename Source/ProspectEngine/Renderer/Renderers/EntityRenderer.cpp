#include "ProspectEngine_pch.h"

#include "EntityRenderer.h"

#include "Scene/Scene_impl.h"
#include "Resources/Resources.h"
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Scene/Mesh_impl.h"

using namespace Prospect;
EntityRenderer::EntityRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetBlinnPhongShader())
{
   m_entityRenderDataLibrary.SetInitialise(InitialiseEntity);
   m_entityRenderDataLibrary.SetDispose(DisposeEntity);
   m_meshRenderDataLibrary.SetInitialise(InitialiseMesh);
   m_meshRenderDataLibrary.SetDispose(DisposeMesh);
}

EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::Render(Entity_impl& entity)
{
   if (entity.GetMeshImpl() != nullptr && entity.GetMaterialImpl() != nullptr)
   {
      Mesh_impl& mesh = *entity.GetMeshImpl();
      MeshRenderData renderData = m_meshRenderDataLibrary.GetRenderData(mesh.GetId());

      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //TEMP: For premultiplied alpha.


      m_shader.Bind();

      m_shader.Update(EntityUniforms(entity));

      if (mesh.GetPositions().size() > 0)
      {
         if (mesh.IsDirty())
         {
            UpdateMesh(renderData, mesh);

            mesh.SetIsDirty(false);
         }

         glBindVertexArray(renderData.VAO);

         glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);
      }
   }
}

void EntityRenderer::InitialiseEntity(EntityRenderData& renderData)
{
   //Do nothing.
}

void EntityRenderer::DisposeEntity(EntityRenderData& renderData)
{
   //Do nothing.
}

void EntityRenderer::InitialiseMesh(MeshRenderData& renderData)
{
   glCreateVertexArrays(1, &renderData.VAO);
}

void EntityRenderer::DisposeMesh(MeshRenderData& renderData)
{
   glDeleteBuffers(renderData.BUFFER_COUNT, renderData.Buffers);
   glDeleteVertexArrays(1, &renderData.VAO);
}

void EntityRenderer::UpdateMesh(MeshRenderData& renderData, const Mesh_impl& mesh)
{
   //Reset buffers
   glDeleteBuffers(renderData.BUFFER_COUNT, renderData.Buffers);
   glCreateBuffers(renderData.BUFFER_COUNT, renderData.Buffers);

   //Create vertex buffer.
   auto& vertices = mesh.GetPositions();

   glNamedBufferStorage(
      renderData.Buffers[renderData.BUFFER_VERTICES],
      vertices.size() * sizeof(glm::vec3),
      &vertices[0],
      0);

   glVertexArrayVertexBuffer(
      renderData.VAO,
      0,
      renderData.Buffers[renderData.BUFFER_VERTICES],
      0,
      sizeof(glm::vec3));

   glVertexArrayAttribFormat(
      renderData.VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderData.VAO, 0, 0);
   glEnableVertexArrayAttrib(renderData.VAO, 0);

   //Create index buffer.
   auto& indices = mesh.GetIndices();

   glNamedBufferStorage(
      renderData.Buffers[renderData.BUFFER_INDICES],
      indices.size() * sizeof(unsigned int),
      &indices[0],
      0);

   glVertexArrayElementBuffer(
      renderData.VAO,
      renderData.Buffers[renderData.BUFFER_INDICES]);

   //Create normals buffer.
   auto& normals = mesh.GetNormals();

   glNamedBufferStorage(
      renderData.Buffers[renderData.BUFFER_NORMALS],
      normals.size() * sizeof(glm::vec3),
      &normals[0],
      0);

   glVertexArrayVertexBuffer(
      renderData.VAO,
      1,
      renderData.Buffers[renderData.BUFFER_NORMALS],
      0,
      sizeof(glm::vec3));

   glVertexArrayAttribFormat(
      renderData.VAO,
      1,
      3,
      GL_FLOAT,
      GL_FALSE, //TODO: true
      0);

   glVertexArrayAttribBinding(renderData.VAO, 1, 1);
   glEnableVertexArrayAttrib(renderData.VAO, 1);
}
