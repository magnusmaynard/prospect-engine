#include "ProspectEngine_pch.h"

#include "ObjReader.h"

#include <string>
#include "Include/Mesh.h"
#include <fstream> 
#include <sstream>

using namespace Prospect;
using namespace glm;

bool ObjReader::Read(Mesh& mesh, const std::string& filename)
{
   mesh.Clear();
   const Obj obj = ParseObj(filename);

   AddObjToMesh(mesh, obj);

   return false;
}

template<typename T>
void ObjReader::Split(const std::string &line, const char delimiter, T result)
{
   std::stringstream stream(line);
   std::string token;

   while (getline(stream, token, delimiter))
   {
      *(result++) = token;
   }
}

std::vector<std::string> ObjReader::Split(const std::string &line, const char delimiter)
{
   std::vector<std::string> tokens;
   Split(line, delimiter, back_inserter(tokens));

   return tokens;
}

vec3 ObjReader::ParseVec3(const std::string& line)
{
   auto tokens = Split(line, ' ');
   return { stof(tokens[1]), stof(tokens[2]), stof(tokens[3]) };
}

ObjReader::Face ObjReader::ParseFace(const std::string& line)
{
   Face face;
   auto tokens = Split(line, ' ');

   for (int i = 1; i < 4; ++i)
   {
      const auto token = Split(tokens[i], '/');
      face.PositionIndices.push_back(stoi(token[0]) - 1);
      face.NormalIndices.push_back(stoi(token[2]) - 1);
   }

   return face;
}

bool ObjReader::ParseSmoothingEnabled(const std::string& line)
{
   auto tokens = Split(line, ' ');

   auto value = tokens[1];

   if (value == "1")
   {
      //Smoothed normals.
      return true;
   }

   //Flat normals.
   return false;
}

ObjReader::Obj ObjReader::ParseObj(const std::string& filename)
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
         obj.SmoothingEnabled = ParseSmoothingEnabled(line);
      }
   }

   return obj;
}

void ObjReader::AddObjToMesh(Mesh& mesh, const Obj& obj)
{
   //Add normals per face.
   auto& positions = mesh.GetPositions();
   auto& normals = mesh.GetNormals();
   auto& indices = mesh.GetIndices();

   for (auto& face : obj.Faces)
   {
      const int faceIndex = static_cast<int>(positions.size());

      for (int i = 0; i < 3; ++i)
      {
         positions.push_back(obj.Positions[face.PositionIndices[i]]);
         normals.push_back(obj.Normals[face.NormalIndices[i]]);
         indices.push_back(faceIndex + i);
      }
   }
}