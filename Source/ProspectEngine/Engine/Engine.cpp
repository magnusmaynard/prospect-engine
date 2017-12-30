#include "ProspectEngine_pch.h"

#include "Include/Engine.h"

#include "Engine_impl.h"
#include "Include/MaterialLibrary.h"

using namespace Prospect;

Engine::Engine(
   IApplication& application,
   const glm::ivec2& size)
   :
   m_impl(std::make_unique<Engine_impl>(*this, application, size))
{
}

void Engine::Start()
{
   m_impl->Start();
}

void Engine::SetTitle(const std::string& title)
{
   m_impl->SetTitle(title);
}

void Engine::EnableCameraControls(bool isEnabled)
{
   m_impl->EnableCameraControls(isEnabled);
}

void Engine::ShowFPS(bool showFPS)
{
   m_impl->ShowFPS(true);
}

void Engine::ShowWireframe(bool showWireframe)
{
   m_impl->ShowWireframe(showWireframe);
}

void Engine::Close()
{
   m_impl->Close();
}

glm::ivec2 Engine::GetSize() const
{
   return m_impl->GetSize();
}

Scene& Engine::GetScene()
{
   return m_impl->GetScene();
}

MeshLibrary& Engine::GetMeshLibrary()
{
   return m_impl->GetMeshLibrary();
}

MaterialLibrary& Engine::GetMaterialLibrary()
{
   return m_impl->GetMaterialLibrary();
}

//Using a unique_ptr means the Engine must have a default destructor. See:
//"Effect Modern C++ - Item 22: When using the Pimpl Idiom, define special member functions in the implementation file."
Engine::~Engine() = default;