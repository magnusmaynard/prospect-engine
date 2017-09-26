#include "Include/Scene.h"
#include "Scene_impl.h"

using namespace Prospect;

Scene::Scene()
   :
   m_impl(std::make_unique<Scene_impl>(*this))
{
}

Scene::~Scene() = default;

Entity& Scene::AddEntity(Mesh* mesh, Material* material)
{
   return m_impl->AddEntity(mesh, material);
}

Entity& Scene::GetEntity(const int index)
{
   return m_impl->GetEntityAtIndex(index);
}

const Camera& Scene::GetCamera() const
{
   return m_impl->GetCamera();
}

Camera& Scene::GetCamera()
{
   return m_impl->GetCamera();
}
