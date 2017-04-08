#version 450

uniform vec3 sunDirection;

in VS_OUT
{
   vec3 normal;
} fs_in;

out vec4 color;

vec3 diffuse = vec3(0.6, 0.6, 0.6);

void main()
{
   float lighting = max(dot(fs_in.normal, sunDirection), 0.1); //0.0

   color = vec4(diffuse * lighting, 1.0);
}