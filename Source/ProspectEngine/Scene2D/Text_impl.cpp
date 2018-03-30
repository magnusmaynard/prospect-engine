#include "ProspectEngine_pch.h"

#include "Scene2D/Text_impl.h"

using namespace Prospect;
using namespace glm;

Text_impl::Text_impl(const std::string& text, const glm::ivec2& position)
{
   SetText(text);
   SetPosition(position);
}

void Text_impl::SetText(const std::string& text)
{
   if (m_text != text)
   {
      m_text = text;

      m_isDirty = true;
   }
}

void Text_impl::SetPosition(const ivec2& position)
{
   if (m_position != position)
   {
      m_position = position;

      m_transform = translate(mat4(), vec3(m_position.x, m_position.y, -10));
   }
}

const std::string& Text_impl::GetText() const
{
   return m_text;
}

const ivec2& Text_impl::GetPosition() const
{
   return m_position;
}

const mat4& Text_impl::GetTransform() const
{
   return m_transform;
}
