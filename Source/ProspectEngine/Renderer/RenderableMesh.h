#pragma once
#include "RendererDefines.h"

#include "Include/Mesh.h"

namespace Prospect
{
   class RenderableMesh
   {
   public:
      RenderableMesh(Mesh& mesh);
      ~RenderableMesh();
      RenderableMesh(const RenderableMesh& other) = delete;
      RenderableMesh& operator=(const RenderableMesh &) = delete;
      RenderableMesh(RenderableMesh&& other);
      RenderableMesh& operator=(RenderableMesh&& other) = delete;

      void Render();

   private:
      void UpdateBuffers();

      Mesh& m_mesh;
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
