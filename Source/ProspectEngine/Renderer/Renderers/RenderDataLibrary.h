#pragma once

#include <functional>

namespace Prospect
{
   template<typename D>
   class RenderDataLibrary
   {
   public:
      RenderDataLibrary(std::function<void(D&)> initialise, std::function<void(D&)> dispose)
         :
         m_initialise(initialise),
         m_dispose(dispose)
      {
      }

      ~RenderDataLibrary()
      {
         for (auto& renderData : m_renderDataMap)
         {
            m_dispose(renderData.second);
         }
      }

      D& GetRenderData(unsigned id)
      {
         auto itr = m_renderDataMap.find(id);
         if (itr == m_renderDataMap.end())
         {
            D renderData;

            m_initialise(renderData);

            return m_renderDataMap.emplace(id, renderData).first->second;
         }

         return itr->second;
      }

   private:
      std::map<unsigned, D> m_renderDataMap;
      std::function<void(D&)> m_initialise;
      std::function<void(D&)> m_dispose;
   };
}