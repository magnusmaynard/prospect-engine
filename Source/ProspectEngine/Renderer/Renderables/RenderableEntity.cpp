#include "ProspectEngine_pch.h"

#include "RenderableEntity.h"

#include "Scene/Scene_impl.h"
#include "Renderer/VertexData.h"
#include "Resources/Resources.h"
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"
#include "Renderer/Pipeline/ShaderLibrary.h"

using namespace Prospect;
RenderableEntity::RenderableEntity(
   ShaderLibrary& shaderLibrary,
   Entity_impl& entity,
   VertexData& vertexData)
   :
   m_entity(entity),
   m_vertexData(vertexData),
   m_shader(shaderLibrary.GetBlinnPhongShader())
{
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

   m_shader.Update(EntityUniforms(m_entity));
   
   m_vertexData.Render();
}

void RenderableEntity::MakeDirty()
{
   //TODO: Implement.
}
