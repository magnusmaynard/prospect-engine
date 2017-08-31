#pragma once
#include <string>

struct Shaders
{
   Shaders(
      std::string& vertex,
      std::string& geometry,
      std::string& tessControl,
      std::string& tessEvaluation,
      std::string& fragment)
      :
      Vertex(vertex),
      Geometry(geometry),
      TessControl(tessControl),
      TessEvaluation(tessEvaluation),
      Fragment(fragment)
   {}

   std::string Vertex;
   std::string Geometry;
   std::string TessControl;
   std::string TessEvaluation;
   std::string Fragment;
};
