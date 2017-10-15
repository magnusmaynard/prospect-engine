#include "ProspectEngine_pch.h"

#include "RenderableEntity.h"

#include "Scene/Scene_impl.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Resources/Resources.h"

using namespace Prospect;

RenderableEntity::RenderableEntity(Entity_impl& entity, VertexData& vertexData)
   :
   m_entity(entity),
   m_vertexData(vertexData),
   m_shader(ShaderFactory::CreateShader(Resources::SIMPLE_VERTEX_SHADER, Resources::SIMPLE_FRAGMENT_SHADER))
{
}

RenderableEntity::~RenderableEntity()
{
   //TODO: shaderFactory decrement references.
}

RenderableEntity::RenderableEntity(RenderableEntity&& other)
   :
   m_entity(other.m_entity),
   m_shader(other.m_shader),
   m_vertexData(other.m_vertexData)
{
}

void RenderableEntity::Render(UniformBuffer& uniformBuffer)
{
   m_shader.Bind();

   uniformBuffer.Bind();

   BindTransform(m_entity.GetTransform());

   BindMaterial(*m_entity.GetMaterial());
   
   m_vertexData.Render();
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