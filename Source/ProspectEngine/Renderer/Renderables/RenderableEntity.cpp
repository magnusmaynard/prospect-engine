#include "RenderableEntity.h"

#include <memory>
#include <iostream>
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"
#include "Renderer/UniformBuffer.h"

using namespace Prospect;

RenderableEntity::RenderableEntity(Entity_impl& entity, RenderableMesh& renderableMesh)
   :
   m_entity(entity),
   m_renderableMesh(renderableMesh)
{
   m_program.AddVertexShader("simple");
   m_program.AddFragmentShader("simple");

   m_program.Compile();
}

RenderableEntity::~RenderableEntity()
{
}

RenderableEntity::RenderableEntity(RenderableEntity&& other)
   :
   m_entity(other.m_entity),
   m_program(std::move(other.m_program)),
   m_renderableMesh(other.m_renderableMesh)
{
}

void RenderableEntity::Render(UniformBuffer& uniformBuffer)
{
   m_program.Bind();

   uniformBuffer.Bind();

   BindTransform(m_entity.GetTransform());

   BindMaterial(*m_entity.GetMaterial());
   
   m_renderableMesh.Render();
}

void RenderableEntity::BindTransform(const glm::mat4& transform)
{
   glUniformMatrix4fv(2, 1, GL_FALSE, &transform[0][0]);
}

void RenderableEntity::BindMaterial(const Material& material)
{
   auto& diffuse = material.GetDiffuse();
   float diffuseRGBA[4] = { diffuse.R, diffuse.G, diffuse.B, diffuse.A };

   glUniform4fv(3, 1, diffuseRGBA);
}