#include "ProspectEngine_pch.h"

#include "Scene/Scene_impl.h"

#include "EngineDefines.h"
#include "Scene/Entity_impl.h"

using namespace Prospect;
using namespace glm;

Scene_impl::Scene_impl(Scene& parent)
   :
   m_parent(parent),
   m_camera(DEFAULT_CAMERA_SIZE)
{
   m_rootEntity = &m_entityLib.AddEntity(nullptr, nullptr, nullptr);
}

Camera& Scene_impl::GetCamera()
{
   return m_camera;
}

const Camera& Scene_impl::GetCamera() const
{
   return m_camera;
}

Entity& Scene_impl::AddEntity(Mesh* mesh, Material* material)
{
   return m_rootEntity->AddEntity(mesh, material);
}

Entity& Scene_impl::GetEntityAtIndex(const int index)
{
   return m_rootEntity->GetEntity(index);
}

Entity* Scene_impl::GetRootEntity()
{
   return m_rootEntity;
}

Camera_impl& Scene_impl::GetCameraImpl()
{
   return *m_camera.m_impl;
}

EntityLibrary& Scene_impl::GetEntityLib()
{
   return m_entityLib;
}

void Scene_impl::UpdateTransforms()
{
   mat4 origin;

   m_rootEntity->m_impl->UpdateTransform(origin, false);
}