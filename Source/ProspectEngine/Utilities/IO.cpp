#include "ProspectEngine_pch.h"

#include "Include/Utilities/IO.h"
#include "Include/Bitmap.h"
#include "Include/Mesh.h"

#include <windows.h>
#include <fstream> 
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Prospect;
using namespace glm;

std::string IO::GetExecutablePath()
{
   char buffer[MAX_PATH];
   GetModuleFileNameA(nullptr, buffer, MAX_PATH);

   const auto position = std::string(buffer).find_last_of("\\/");
   return std::string(buffer).substr(0, position + 1);
}

std::string IO::ReadText(const std::string& filePath)
{
   std::ifstream sourceFile(filePath);

   if (!sourceFile)
   {
      std::cerr << "Error: Unable to read file at path: " << filePath << std::endl;
      return "";
   }

   std::stringstream sourceStream;
   sourceStream << sourceFile.rdbuf();

   return sourceStream.str();
}

Bitmap IO::ReadBitmap(const std::string& filePath, const bool monochrome)
{
   const int desiredChannels = monochrome ? 1 : 3;

   int width = 0;
   int height = 0;
   int channels = 0;
   float* rawData = stbi_loadf(filePath.c_str(), &width, &height, &channels, desiredChannels);

   const std::vector<float> data(rawData, rawData + width * height * desiredChannels);
   return Bitmap(width, height, channels, data);
}

struct VertexIndices
{
   int PositionIndex;
   int NormalIndex;
};

struct FaceIndices
{
   VertexIndices A;
   VertexIndices B;
   VertexIndices C;
};

template<typename T>
void Split(const std::string &line, const char delimiter, T result)
{
   std::stringstream stream(line);
   std::string token;

   while (getline(stream, token, delimiter))
   {
      *(result++) = token;
   }
}

std::vector<std::string> Split(const std::string &line, const char delimiter)
{
   std::vector<std::string> tokens;
   Split(line, delimiter, back_inserter(tokens));

   return tokens;
}

glm::vec3 ParseVec3(const std::string& line)
{
   auto tokens = Split(line, ' ');
   return { stof(tokens[1]), stof(tokens[2]), stof(tokens[3]) };
}

struct Face
{
   std::vector<int> PositionIndices;
   std::vector<int> NormalIndices;
};

struct Obj
{
   std::vector<vec3> Positions;
   std::vector<vec3> Normals;
   std::vector<Face> Faces;
   bool Smoothing = false;
   std::string Name;
};


Face ParseFace(const std::string& line)
{
   Face face;
   auto tokens = Split(line, ' ');

   for (int i = 1; i < 4; ++i)
   {
      const auto token = Split(tokens[i], '//');
      face.PositionIndices.push_back(stof(token[0]) - 1);
      face.NormalIndices.push_back(stof(token[2]) - 1);
   }

   return face;
}

Obj ParseObj(const std::string& filename)
{
   auto file = std::fstream(filename, std::fstream::in);
   std::string line;

   Obj obj;

   while (getline(file, line))
   {
      const std::string prefix = line.substr(0, 2);

      if (prefix == "v ") //Vertex positions.
      {
         obj.Positions.push_back(ParseVec3(line));
      }
      else if (prefix == "vn") //Vertex normals.
      {
         obj.Normals.push_back(ParseVec3(line));
      }
      else if (prefix == "f ") //Face indices.
      {
         obj.Faces.push_back(ParseFace(line));
      }
      else if (prefix == "s ") //Smoothing mode.
      {
         //Not implemented.
         obj.Smoothing = false;
      }
   }

   return obj;
}

void AddNormalsPerFace(Mesh& mesh, const Obj& obj)
{
   auto& positions = mesh.GetPositions();
   auto& normals = mesh.GetNormals();
   auto& indices = mesh.GetIndices();

   for (auto& face : obj.Faces)
   {
      const int faceIndex = positions.size();

      for (int i = 0; i < 3; ++i)
      {
         positions.push_back(obj.Positions[face.PositionIndices[i]]);
         normals.push_back(obj.Normals[face.NormalIndices[i]]);
         indices.push_back(faceIndex + i);
      }
   }
}

bool IO::ReadObj(Mesh& mesh, const std::string& filename)
{
   mesh.Clear();
   const Obj obj = ParseObj(filename);

   const bool flatIndexed = true;

   if (flatIndexed)
   {
      AddNormalsPerFace(mesh, obj);
   }
   else
   {
      //Do nothing.
   }

   return false;
}
