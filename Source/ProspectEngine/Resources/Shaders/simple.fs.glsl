#version 450

layout (location = 3) uniform vec4 diffuse;

out vec4 color;

void main()
{
   color = diffuse;
}