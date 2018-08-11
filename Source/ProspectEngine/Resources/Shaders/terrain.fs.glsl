#version 450

layout (binding = 0) uniform sampler2D heightMapTexture;
layout (binding = 1) uniform sampler2D groundTexture;

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

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   mat4 InverseView;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform TerrainUniforms
{
   uint MaterialID;
   float MinHeight;
   float MaxHeight;
   float TotalSize;
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
   uint materialID = terrain.MaterialID;
   Material material = materialLibrary.Materials[materialID];

   float xNeg = textureOffset(heightMapTexture, fs_in.textureCoord, ivec2(-1, 0)).x * terrain.MaxHeight;
   float xPos = textureOffset(heightMapTexture, fs_in.textureCoord, ivec2( 1, 0)).x * terrain.MaxHeight;
   float yNeg = textureOffset(heightMapTexture, fs_in.textureCoord, ivec2( 0,-1)).x * terrain.MaxHeight;
   float yPos = textureOffset(heightMapTexture, fs_in.textureCoord, ivec2( 0, 1)).x * terrain.MaxHeight;
   vec3 va = vec3(2.0, xPos - xNeg, 0);
   vec3 vb = vec3(0, yPos - yNeg, 2.0);

   vec3 normal = mat3(camera.View) * normalize(-cross(va, vb));

   float groundTextureScale = 60;
   vec3 diffuse = texture(groundTexture, fs_in.textureCoord * groundTextureScale).xyz;

   vec4 color = vec4(diffuse, 1.0);

   UpdateBuffers(
      color,
      normal,
      0,
      material.SpecularAndPower.a,
      0.5f,
      materialID,
      0);
}