#version 450

struct Material
{
   vec4 Diffuse;
   vec4 Ambient;
   vec4 SpecularAndPower;
};

layout (std140) uniform MaterialLibraryUniforms
{
   Material Materials[10];
} materialLibrary;

layout (std140) uniform EntityUniforms
{
   mat4 Model;
   mat4 Normal;
   ivec4 MaterialID;
} entity;

in VS_OUT
{
   vec3 Normal;
} fs_in;

layout (location = 0) out vec4 albedo;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 specular;

void main()
{
   int materialID = entity.MaterialID.x;
   
   //Default to zero.
   albedo = vec4(0);
   normal = vec4(0);
   specular = vec4(0);

   //Albedo
   albedo = materialLibrary.Materials[materialID].Diffuse;

   //Normal
   normal.xyz =  fs_in.Normal;
   normal.w = materialID;

   //Specular
   //TODO;
}