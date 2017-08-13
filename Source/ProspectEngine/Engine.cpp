#include "Include/Engine.h"

#include "Engine_impl.h"

using namespace Prospect;

Engine::Engine(
   IApplication& application,
   const int width,
   const int height)
   :
   m_impl(new Engine_impl(application, width, height))
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

void Engine::Clear()
{
   m_impl->Clear();
}

void Engine::SetPolygonMode(const PolygonMode& polygonMode)
{
   m_impl->SetPolygonMode(polygonMode);
}

//Scene& Engine::GetScene()
//{
//   return m_impl->Gen
//}

glm::ivec2 Engine::GetSize() const
{
   return m_impl->GetSize();
}
