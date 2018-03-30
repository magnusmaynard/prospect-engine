#pragma once

namespace Prospect
{
   class Renderable
   {
   public:
      Renderable();

      unsigned GetId() const;

      bool IsDirty() const;
      bool Clean() const;

   private:
      static unsigned m_nextId;

      const unsigned m_id;
      mutable bool m_isDirty;
   };
}