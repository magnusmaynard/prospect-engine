#pragma once
#include "RendererDefines.h"

#include "Scene/Mesh_impl.h"

namespace Prospect
{
   class RenderableMesh
   {
   public:
      RenderableMesh(Mesh_impl& mesh);
      ~RenderableMesh();
      RenderableMesh(const RenderableMesh& other) = delete;
      RenderableMesh& operator=(const RenderableMesh &) = delete;
      RenderableMesh(RenderableMesh&& other);
      RenderableMesh& operator=(RenderableMesh&& other) = delete;

      void Render();

   private:
      void UpdateBuffers();

      Mesh_impl& m_mesh;
      GLuint m_VAO = GL_NULL;

      enum BUFFERS
      {
         BUFFER_VERTICES,
         BUFFER_INDICES,
         BUFFER_COUNT,
      };

      GLuint m_buffers[BUFFER_COUNT];
   };
}
