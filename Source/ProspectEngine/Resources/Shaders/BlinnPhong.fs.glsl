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
   Material material = materialLibrary.Materials[materialID];

   //Albedo buffer
   albedo.rgba = material.Diffuse; //Albedo

   //Normal buffer
   normal.rgb = fs_in.Normal; //Normal
   normal.a = 0; //View dependent roughness

   //Specular buffer
   specular.r = material.SpecularAndPower.a; //Roughness/Specular Power
   specular.g = 10.f; //Specular Intensity
   specular.b = 0; //Material ID
   specular.a = 0; //SSS Translucency
}