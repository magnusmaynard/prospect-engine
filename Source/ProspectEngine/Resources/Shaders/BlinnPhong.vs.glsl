#version 450

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
   vec3 Normal;
} vs_out;

void main()
{
   vs_out.Normal = mat3(camera.View * entity.Normal) * normal;

   gl_Position = camera.PerspectiveProjection * camera.View * entity.Model * vec4(point, 1.0);
}
