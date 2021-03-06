#pragma once
#include "Renderer/Pipeline/Shaders/BlinnPhongShader.h"

#include <string>

namespace Prospect
{
   struct Frustum;
   class ShaderLibrary;

   class Debug
   {
   public:
      //Checks OpenGL for any errors.
      //Pops from the error stack and outputs to the console.
      static void CheckErrors();

      //Outputs a value.
      template <typename T>
      static void Write(const T& value);

      //Outputs a value as a new line.
      template <typename T>
      static void WriteLine(const T& value);

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

         static void AddFrustumToPoints(std::vector<glm::vec3>& points, const Frustum& frustum, const glm::mat4& transform);
         static void AddBoundsToPoints(std::vector<glm::vec3>& points, const Bounds& bounds, const glm::mat4& transform);

      private:
         static void Render(std::vector<glm::vec3>& points, const Color& color);
      };

   private:
      template <typename T>
      static std::string ConvertToString(const T& string);

      static std::string ConvertToString(const std::string& string) { return string; }

      static std::string ConvertToString(const char* chars) { return chars; }
   };

   template <typename T>
   void Debug::Write(const T& value)
   {
#ifdef _DEBUG
      //Uses std::to_string or glm::to_string.
      std::cout << ConvertToString(value);
#endif
   }

   template <typename T>
   void Debug::WriteLine(const T& value)
   {
#ifdef _DEBUG
      Write(value);
      std::cout << std::endl;
#endif
   }

   template <typename T>
   std::string Debug::ConvertToString(const T& string)
   {
      return to_string(string);
   }
}
