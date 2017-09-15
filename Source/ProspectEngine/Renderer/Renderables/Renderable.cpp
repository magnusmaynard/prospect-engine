#include "Renderable.h"

#include <memory>
#include <iostream>
#include "Scene/Scene_impl.h"
#include "Scene/Camera_impl.h"

using namespace Prospect;

Renderable::Renderable(
   Entity_impl& entity,
   RenderableMesh& renderableMesh,
   RenderableMaterial& renderableMaterial)
   :
   m_entity(entity),
   m_renderableMesh(renderableMesh),
   m_renderableMaterial(renderableMaterial)
{
   m_program.AddVertexShader("simple");
   m_program.AddFragmentShader("simple");

   m_program.Compile();
}

Renderable::~Renderable()
{
}

Renderable::Renderable(Renderable&& other)
   :
   m_entity(other.m_entity),
   m_program(std::move(other.m_program)),
   m_renderableMesh(other.m_renderableMesh),
   m_renderableMaterial(other.m_renderableMaterial)
{
}

void Renderable::Render(Scene_impl& scene)
{
   m_program.Use();

   UseCamera(scene.GetCameraImpl());

   UseTransform(m_entity.GetTransform());

   m_renderableMaterial.Use();

   m_renderableMesh.Render();
}

void Renderable::UseCamera(const Camera_impl& camera)
{
   glUniformMatrix4fv(0, 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
}

void Renderable::UseTransform(const glm::mat4& transform)
{
   glUniformMatrix4fv(2, 1, GL_FALSE, &transform[0][0]);
}
