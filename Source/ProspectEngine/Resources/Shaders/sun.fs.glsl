#version 450

struct Material
{
   vec4 Diffuse;
   vec4 Ambient;
   vec4 SpecularAndPower;
   ivec4 IsLit;
};

layout (std140) uniform MaterialLibraryUniforms
{
   Material Materials[10];
} materialLibrary;

layout (std140) uniform SunUniforms
{
   mat4 Model;
   uvec4 MaterialID;
} sun;

in VS_OUT
{
   vec3 Normal;
} fs_in;

layout (location = 0) out vec4 albedoBuffer;
layout (location = 1) out vec4 normalBuffer;
layout (location = 2) out vec4 specularBuffer;

void UpdateBuffers(
   vec4 albedo,
   vec3 normal,
   float viewDependentRoughness,
   float specularPower,
   float specularIntensity,
   float materialID,
   float SSSTranslucency)
{
   //Albedo buffer
   albedoBuffer.rgba = albedo;

   //Normal buffer
   normalBuffer.rgb = normal;
   normalBuffer.a = viewDependentRoughness;

   //Specular buffer
   specularBuffer.r = specularPower;
   specularBuffer.g = specularIntensity;
   specularBuffer.b = materialID;
   specularBuffer.a = SSSTranslucency;
}

void main()
{
   uint materialID = sun.MaterialID.x;
   Material material = materialLibrary.Materials[materialID];

   UpdateBuffers(
      material.Diffuse,
      fs_in.Normal,
      0,
      material.SpecularAndPower.a,
      10.f,
      materialID,
      0);
}