#pragma once

namespace Prospect
{
   class Mesh;

   class ObjReader
   {
   public:
      static bool ObjReader::Read(Mesh& mesh, const std::string& filename);

   private:
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

      struct Face
      {
         std::vector<int> PositionIndices;
         std::vector<int> NormalIndices;
      };

      struct Obj
      {
         std::vector<glm::vec3> Positions;
         std::vector<glm::vec3> Normals;
         std::vector<Face> Faces;
         bool SmoothingEnabled = false;
         std::string Name;
      };

      template<typename T>
      static void Split(const std::string &line, const char delimiter, T result);

      static std::vector<std::string> Split(const std::string &line, const char delimiter);

      static glm::vec3 ParseVec3(const std::string& line);

      static Face ParseFace(const std::string& line);

      static bool ParseSmoothingEnabled(const std::string& line);

      static Obj ParseObj(const std::string& filename);

      static void AddObjToMesh(Mesh& mesh, const Obj& obj);
   };
}
