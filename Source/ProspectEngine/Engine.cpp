#include "Include/Engine.h"

#include "Engine_impl.h"

using namespace Prospect;

Engine::Engine(
   IApplication& application,
   const int width,
   const int height)
   :
   m_impl(std::make_unique<Engine_impl>(*this, application, width, height))
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

void Engine::Close()
{
   m_impl->Close();
}

Scene& Engine::GetScene()
{
   return m_impl->GetScene();
}

glm::ivec2 Engine::GetSize() const
{
   return m_impl->GetSize();
}

//Using a unique_ptr means the Engine must have a default destructor. See:
//"Effect Modern C++ - Item 22: When using the Pimpl Idiom, define special member functions in the implementation file."
Engine::~Engine() = default;