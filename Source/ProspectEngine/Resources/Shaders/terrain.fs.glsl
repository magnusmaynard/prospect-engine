#version 450

layout (binding = 0) uniform sampler2D textureHeight;

uniform float minHeight;
uniform float maxHeight;

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

struct DirectionalLight
{
   vec4 Position;
   vec4 Direction;
   vec4 ColorAndBrightness;
   vec4 ShadowMapIndex;
};

layout (std140) uniform DirectionalLightListUniforms
{
   DirectionalLight Lights[10];
   vec2 Count;
} directionalLights;

layout (std140) uniform NodeUniforms
{
   vec4 Origin;
   ivec4 Edges;
   float Size;
   float Level;
} node;

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

DirectionalLight light = directionalLights.Lights[0];
vec3 lightColor = light.ColorAndBrightness.rgb;
float lightBrightness = light.ColorAndBrightness.a;

void main()
{
   float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x * maxHeight;
   float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x * maxHeight;
   float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x * maxHeight;
   float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x * maxHeight;
   vec3 va = normalize(vec3(2.0, xPos - xNeg, 0));
   vec3 vb = normalize(vec3(0, yPos - yNeg, 2.0));

   float height = texture(textureHeight, fs_in.textureCoord).r * 0.2;
   vec3 normal = mat3(camera.View) * vec3(cross(va, vb));

   vec3 diffuse = vec3(0.1 + height);

   vec4 color = vec4(diffuse, 1.0);

   UpdateBuffers(
      color,
      normal,
      0,
      16.f,
      0.f,
      -1,
      0);
}