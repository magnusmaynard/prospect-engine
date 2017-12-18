#version 450

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 ViewDirection;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 Color;
   vec4 Brightness;
} light;

layout (std140) uniform EntityUniforms
{
   mat4 Model;
   mat4 Normal;
   ivec4 MaterialID;
} entity;

layout (location = 0) in vec3 point;
layout (location = 1) in vec3 normal;

out VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} vs_out;

void main()
{
   // mat3 normalMatrix = transpose(inverse(mat3(entity.Model)));
   
   vec4 P = camera.View * entity.Model * vec4(point, 1.0);

   vs_out.N = mat3(camera.View * entity.Normal) * normal;
   vs_out.L = mat3(camera.View) * -light.Direction.xyz;
   vs_out.V = -P.xyz;

   gl_Position = camera.PerspectiveProjection * P;
}
