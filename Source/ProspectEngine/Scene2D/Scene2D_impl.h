#pragma once
#include "Scene2D/Text_impl.h"

namespace Prospect
{
   class Scene2D_impl
   {
   public:
      Text_impl& AddText()
      {
         return m_texts.emplace_back("", glm::ivec2(0,0));
      }

      int GetTextCount() const
      {
         return static_cast<int>(m_texts.size());
      }

      Text_impl& GetTextByIndex(const int index)
      {
         return m_texts[index];
      }

   private:
      std::vector<Text_impl> m_texts;
   };
}
