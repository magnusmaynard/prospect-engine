#version 450

in GS_OUT
{
   vec3 Normal;
   vec3 InverseNormal;
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
   // vec4 diffuse = vec4(0.52, 0.65, 0.21, 1);
   // vec4 diffuse = vec4(0.43, 0.52, 0.21, 1);
   // vec4 diffuse = vec4(0.43, 0.56, 0.11, 1);
   vec4 diffuse = vec4(0.40, 0.53, 0.10, 1);

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
      diffuse,
      normal,
      0,
      2,
      0.5f,
      0,
      0);
}