#pragma once

#include <functional>

namespace Prospect
{
   template<typename D>
   class RenderDataLibrary
   {
   public:
      RenderDataLibrary()
         :
         m_initialise(DefaultInitialise),
         m_dispose(DefaultDispose)
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
            renderData.Initialised = false;

            m_initialise(renderData);

            return m_renderDataMap.emplace(id, renderData).first->second;
         }

         return itr->second;
      }

      void SetInitialise(std::function<void(D&)> initialise)
      {
         m_initialise = initialise;
      }

      void SetDispose(std::function<void(D&)> dispose)
      {
         m_dispose = dispose;
      }

      static void DefaultInitialise(D& renderData)
      {
         //Do nothing.
      }

      static void DefaultDispose(D& renderData)
      {
         if(renderData.Initialised)
         {
            std::cerr << "Warning: Initialised render data is not being disposed";
         }

         //Do nothing.
      }

   private:
      std::map<unsigned, D> m_renderDataMap;
      std::function<void(D&)> m_initialise;
      std::function<void(D&)> m_dispose;
   };
}