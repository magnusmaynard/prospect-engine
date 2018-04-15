#pragma once

namespace Prospect
{
   enum class Key
   {
      None,
      D1,
      D2,
      D3,
      D4,
      D5,
      D6,
      D7,
      D8,
      D9,
      D0,
      W,
      S,
      A,
      D,
      C,
      Space,
      Escape,
      PrintScreen
   };

   enum class KeyModifier
   {
      None = 0,
      Shift = 1,
      Control = 2,
      Alt = 4,
   };
}