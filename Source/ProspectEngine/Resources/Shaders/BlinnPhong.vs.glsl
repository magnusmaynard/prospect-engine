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
   vec4 DiffuseColor;
} light;

layout (location = 2) uniform mat4 model;

layout (location = 0) in vec3 point;
layout (location = 1) in vec3 normal;

out VS_OUT
{
   smooth vec3 N; //TODO: Remove smooth.
   smooth vec3 L;
   smooth vec3 V;   
} vs_out;

void main()
{
   vec4 position = vec4(point, 1.0);
   mat4 modelView = camera.View * model;

   vec4 P = modelView * position;

   vs_out.N = mat3(model) * normal;
   vs_out.L = -light.Direction.xyz;
   vs_out.V = camera.ViewDirection.xyz;

   gl_Position = camera.PerspectiveProjection * P;
}
