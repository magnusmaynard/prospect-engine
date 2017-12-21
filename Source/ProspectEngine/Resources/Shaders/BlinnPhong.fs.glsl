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
   vec3 N;
   vec3 V;
   vec3 Position;
} fs_in;

layout (location = 0) out vec4 albedo;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 specular;

void main()
{
   vec4 outColor0 = vec4(0);
   vec4 outColor1 = vec4(0);

   outColor0.xyz = fs_in.Position;
   outColor0.w = entity.MaterialID.x;

   outColor1.xyz = fs_in.N;

   albedo =  outColor0;
   normal =  outColor1;
}