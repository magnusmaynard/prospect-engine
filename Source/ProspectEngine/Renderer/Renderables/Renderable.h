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

   protected:
      const unsigned m_id;
      mutable bool m_isDirty;

   private:
      static unsigned m_nextId;
   };
}