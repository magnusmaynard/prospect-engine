#include "Renderable.h"
#include <memory>

using namespace Prospect;

Renderable::Renderable(Entity_impl& entity)
   :
   m_entity(&entity)
{
   m_program.AddVertexShader("simple");
   m_program.AddFragmentShader("simple");

   m_program.Compile();

   //Get uniform bindings

   UpdateVertexData();
}

Renderable::~Renderable()
{ 
   //TODO: delete VAO and buffers
}


Renderable::Renderable(Renderable&& other)
   :
   m_entity(other.m_entity),
   m_program(std::move(other.m_program)),
   m_VAO(other.m_VAO)
{
   other.m_VAO = -1;
}

Renderable& Renderable::operator=(Renderable&& other)
{
   if(this != &other)
   {
      m_entity = other.m_entity;
      m_program = std::move(other.m_program);
      m_VAO = other.m_VAO;

      other.m_VAO = -1;
   }

   return *this;
}

void Renderable::UpdateVertexData()
{
   Mesh& mesh = m_entity->GetMesh();

   if (mesh.IsDirty())
   {
      mesh.SetIsDirty(false);

      //TODO: Reset and delete buffers.

      glCreateVertexArrays(1, &m_VAO); //TODO: move into to constructor and move constructors.

      glCreateBuffers(BUFFER_COUNT, m_buffers);

      //Create vertex buffer.
      auto& vertices = mesh.GetVertices();

      glNamedBufferStorage(
         m_buffers[BUFFER_VERTICES],
         vertices.size() * sizeof(glm::vec3),
         &vertices[0],
         0);

      glVertexArrayVertexBuffer(
         m_VAO,
         0,
         m_buffers[BUFFER_VERTICES],
         0,
         sizeof(glm::vec3));

      glVertexArrayAttribFormat(
         m_VAO,
         0,
         3,
         GL_FLOAT,
         GL_FALSE,
         0);

      glVertexArrayAttribBinding(m_VAO, 0, 0);
      glEnableVertexArrayAttrib(m_VAO, 0);

      glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_VERTICES]);

      //Create index buffer.
      auto& indices = mesh.GetIndices();

      glNamedBufferStorage(
         m_buffers[BUFFER_INDICES],
         indices.size() * sizeof(unsigned int),
         &indices[0],
         0);

      glVertexArrayElementBuffer(m_VAO, m_buffers[BUFFER_INDICES]);
   }
}

void Renderable::Render(Scene_impl& scene)
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //TODO: move somewhere else.

   Mesh& mesh = m_entity->GetMesh();

   if(mesh.GetVertices().size() == 0)
   {
      return;
   }

   UpdateVertexData();

   m_program.Use();

   //Apply transform
   //m_entity.GetTransform();

   //Apply Material
   //m_entity.GetMaterial();

   //Apply Mesh
   glBindVertexArray(m_VAO);

   //Render
   glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);


}
