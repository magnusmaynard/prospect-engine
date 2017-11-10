#version 450

layout (std140) uniform CameraUniforms
{
   mat4 Projection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 DiffuseColor;
} light;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

layout (location = 0) in vec3 point;
layout (location = 1) in vec3 normal;

out VS_OUT
{
   vec3 Normal;
} vs_out;

void main()
{
   vs_out.Normal = normal;

   gl_Position = camera.Projection * camera.View * model * vec4(point, 1.0);
}
