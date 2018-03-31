#version 450

layout (binding = 0) uniform sampler2D textureHeight;

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform TerrainUniforms
{
   float MinHeight;
   float MaxHeight;
   float TotalSize;
   float Null;
} terrain;

in TES_OUT
{
   vec2 textureCoord;
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
   float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x * terrain.MaxHeight;
   float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x * terrain.MaxHeight;
   float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x * terrain.MaxHeight;
   float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x * terrain.MaxHeight;
   vec3 va = vec3(2.0, xPos - xNeg, 0);
   vec3 vb = vec3(0, yPos - yNeg, 2.0);

   vec3 normal = mat3(camera.View) * normalize(-cross(va, vb));
   vec3 diffuse = vec3(0.1);//TODO: get color

   vec4 color = vec4(diffuse, 1.0);

   UpdateBuffers(
      color,
      normal,
      0,
      16.f,
      0.5f,
      10,
      0);
}