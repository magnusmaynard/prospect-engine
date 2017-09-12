#include "Renderable.h"

#include <memory>
#include <iostream>
#include "Scene/Scene_impl.h"

using namespace Prospect;

Renderable::Renderable(Entity_impl& entity, RenderableMesh& renderableMesh)
   :
   m_entity(&entity),
   m_renderableMesh(renderableMesh)
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
   m_renderableMesh(other.m_renderableMesh)
{
}

void Renderable::Render(Scene_impl& scene)
{
   m_program.Use();

   UseCamera(*scene.GetCamera());

   UseTransform(m_entity->GetTransform());

   UseMaterial(m_entity->GetMaterial());

   m_renderableMesh.Render();
}

void Renderable::UseCamera(const Camera& camera)
{
   glUniformMatrix4fv(0, 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
   glUniformMatrix4fv(1, 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
}

void Renderable::UseTransform(const glm::mat4& transform)
{
   glUniformMatrix4fv(2, 1, GL_FALSE, &transform[0][0]);
}

void Renderable::UseMaterial(const Material& material)
{
   auto& diffuse = material.GetDiffuse();
   float diffuseRGBA[4] = { diffuse.R, diffuse.G, diffuse.B, diffuse.A };

   glUniform4fv(3, 1, diffuseRGBA);
}
