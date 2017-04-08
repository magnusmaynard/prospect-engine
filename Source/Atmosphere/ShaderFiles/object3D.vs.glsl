#version 450

layout (location = 0) in vec3 point;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 sunDirection;

out VS_OUT
{
   vec3 normal;
   vec3 sunDirection;
} vs_out;

void main()
{
   vs_out.normal = normal;
   vs_out.sunDirection = sunDirection;
   gl_Position = projection * view * model * vec4(point, 1.0);
}
