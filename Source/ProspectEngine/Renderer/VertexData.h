#pragma once

#include "Renderer/RendererDefines.h"

namespace Prospect
{
   class Mesh_impl;

   class VertexData
   {
   public:
      VertexData(Mesh_impl& mesh);
      ~VertexData();
      VertexData(const VertexData& other) = delete;
      VertexData& operator=(const VertexData &) = delete;
      VertexData(VertexData&& other);
      VertexData& operator=(VertexData&& other) = delete;

      void Render();

   private:
      void UpdateBuffers();

      Mesh_impl& m_mesh;
      GLuint m_VAO = GL_NULL;

      enum BUFFERS
      {
         BUFFER_VERTICES,
         BUFFER_INDICES,
         BUFFER_NORMALS,
         BUFFER_COUNT,
      };

      GLuint m_buffers[BUFFER_COUNT];
   };
}
