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
   m_shader(ShaderFactory::CreateBlinnPhongShader())
{
   globalUniformBuffers.Camera.Bind(m_shader);
   globalUniformBuffers.DirectionalLight.Bind(m_shader);
   globalUniformBuffers.Materials.Bind(m_shader);
}

RenderableEntity::~RenderableEntity()
{
   //TODO: shaderFactory decrement references.
}

RenderableEntity::RenderableEntity(RenderableEntity&& other)
   :
   m_entity(other.m_entity),
   m_vertexData(other.m_vertexData),
   m_shader(other.m_shader)
{
}

void RenderableEntity::Render()
{
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

   m_shader.Bind();

   BindTransform(m_entity.GetTransform());

   BindMaterial(*m_entity.GetMaterialImpl());
   
   m_vertexData.Render();
}

void RenderableEntity::MakeDirty()
{
   //TODO: Implement.
}

void RenderableEntity::BindTransform(const glm::mat4& transform)
{
   glUniformMatrix4fv(2, 1, GL_FALSE, &transform[0][0]);
}

void RenderableEntity::BindMaterial(const Material_impl& material)
{
   glUniform1i(100, material.GetID());
}