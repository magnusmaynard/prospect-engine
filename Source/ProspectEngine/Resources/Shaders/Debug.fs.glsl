#version 450

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
   UpdateBuffers(
      vec4(1, 0, 0, 1),
      vec3(0, 1, 0),
      0,
      0,
      0,
      0,
      0);
}