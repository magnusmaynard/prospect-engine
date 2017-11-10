#include "ProspectEngine_pch.h"

#include "RenderableEntity.h"

#include "Scene/Scene_impl.h"
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Resources/Resources.h"

using namespace Prospect;

RenderableEntity::RenderableEntity(
   const GlobalUniformBuffers& globalUniformBuffers,
   Entity_impl& entity,
   VertexData& vertexData)
   :
   m_entity(entity),
   m_vertexData(vertexData),
   m_shader(ShaderFactory::CreateShader(Resources::BLINNPHONG_VERTEX_SHADER, Resources::BLINNPHONG_FRAGMENT_SHADER))
{
   globalUniformBuffers.Camera.Bind(m_shader);
   globalUniformBuffers.DirectionalLight.Bind(m_shader);
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

void RenderableEntity::Render()
{
   m_shader.Bind();

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

   glUniform4fv(5, 1, &diffuse.ToRGBA()[0]);
}