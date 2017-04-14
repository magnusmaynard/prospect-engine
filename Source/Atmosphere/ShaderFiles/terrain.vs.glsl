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
   vs_out.normal = (model * vec4(normal, 1.0)).xyz;
   vs_out.sunDirection = sunDirection;//(view * model * vec4(sunDirection, 1.)).xyz;
   gl_Position = projection * view * model * vec4(point, 1.0);
}
