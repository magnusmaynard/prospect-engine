#pragma once
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"

#include <string>

namespace Prospect
{
   class ShaderLibrary;

   class Debug
   {
   public:
      //Checks OpenGL for any errors.
      //Pops from the error stack and outputs to the console.
      static void CheckErrors();

      //Outputs a value.
      template <typename T>
      static void Write(const T& value)
      {
#ifdef _DEBUG
         //Uses std::to_string or glm::to_string.
         std::cout << to_string(value);
#endif
      }

      //Outputs a value as a new line.
      template <typename T>
      static void WriteLine(const T& value)
      {
#ifdef _DEBUG
         Write(value);
         std::cout << std::endl;
#endif
      }

      //Allows for drawing a list of points.
      //To be used for debugging only.
      class Points
      {
      public:
         //Setup the shaders and buffers.
         static void Initialise(ShaderLibrary& shaderLibrary);

         //Set the points that will be drawn.
         static void Set1(std::vector<glm::vec3>& points);
         static void Set2(std::vector<glm::vec3>& points);

         //Call during geometry pass.
         static void Render();

      private:
         static void Render(std::vector<glm::vec3>& points);
      };
   };
}
