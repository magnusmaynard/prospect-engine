#version 450

layout (location = 4) uniform vec3 diffuse;

out vec4 color;

void main()
{
   color = vec4(diffuse, 1);
}