#pragma once

namespace Prospect
{
   enum class Key
   {
      None,
      W,
      S,
      A,
      D,
      Escape,
   };

   enum class KeyModifier
   {
      None = 0,
      Shift = 1,
      Control = 2,
      Alt = 4,
   };
}