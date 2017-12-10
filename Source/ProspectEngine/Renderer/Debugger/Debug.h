#pragma once

namespace Prospect
{
   class Debug
   {
   public:
      //Checks OpenGL for any errors.
      //Pops from the error stack and outputs to the console.
      static void CheckErrors();
   };
}
