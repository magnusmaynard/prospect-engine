#pragma once
#include "Renderer/UniformBuffer.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Prospect;

void UniformBuffer::SetViewTransform(const glm::mat4& viewTransform)
{
   m_viewTransform = viewTransform;
}

void UniformBuffer::SetProjectionTransform(const glm::mat4& projectionTransform)
{
   m_projectionTransform = projectionTransform;
}

void UniformBuffer::Bind()
{
   glUniformMatrix4fv(0, 1, GL_FALSE, &m_projectionTransform[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &m_viewTransform[0][0]);
}