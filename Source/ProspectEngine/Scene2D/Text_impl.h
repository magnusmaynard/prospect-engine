#pragma once
#include "Renderer/Renderables/Renderable.h"

namespace Prospect
{
   class Text_impl : public Renderable
   {
   public:
      Text_impl(const std::string& text, const glm::ivec2& position);

      void SetText(const std::string& text);
      void SetPosition(const glm::ivec2& position);

      const std::string& GetText() const;
      const glm::ivec2& GetPosition() const;
      const glm::mat4& GetTransform() const;

   private:
      std::string m_text;
      glm::ivec2 m_position;
      glm::mat4 m_transform;
   };
}
