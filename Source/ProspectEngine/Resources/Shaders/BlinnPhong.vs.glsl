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

struct Light
{
   vec4 Direction;
   vec4 Color;
   vec4 Brightness;
};

layout (std140) uniform LightsUniforms
{
   Light Lights[10];
   int Count;
} lights;

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
   vec3 V;
   vec3 Position;
} vs_out;

Light light = lights.Lights[0];

void main()
{
   vec4 P = camera.View * entity.Model * vec4(point, 1.0);

   vs_out.N = mat3(camera.View * entity.Normal) * normal;
   vs_out.V = -P.xyz;

   vs_out.Position = P.xyz; //TODO; world space or eyespace?

   gl_Position = camera.PerspectiveProjection * P;
}
