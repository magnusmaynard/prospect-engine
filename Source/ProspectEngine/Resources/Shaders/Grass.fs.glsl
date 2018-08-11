#version 450

layout (location = 0) out vec4 albedoBuffer;
layout (location = 1) out vec4 normalBuffer;
layout (location = 2) out vec4 specularBuffer;

layout(binding = 1) uniform sampler2D noiseTexture;

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

layout (std140) uniform GrassUniforms
{
   vec2 PatchOffset;
   uvec2 MaterialID;
} grass;

in GS_OUT
{
   vec3 Normal;
   vec3 InverseNormal;
} fs_in;

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
   uint materialID = grass.MaterialID.x;
   Material material = materialLibrary.Materials[materialID];

   vec4 diffuseTexel = vec4(texture(noiseTexture, vec2(100, 0)).rgb, 1);

   vec3 normal;
   if(gl_FrontFacing)
   {
      normal = fs_in.Normal;
   }
   else
   {
      normal = fs_in.InverseNormal;
   }

   UpdateBuffers(
      diffuseTexel,//material.Diffuse,
      normal,
      0,
      2,
      0.5f,
      materialID,
      0);
}