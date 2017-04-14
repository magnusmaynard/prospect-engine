#version 450

in VS_OUT
{
   vec3 normal;
   vec3 sunDirection;
} fs_in;

out vec4 color;

vec3 diffuse = vec3(0.6, 0.6, 0.6);

void main()
{
   float lighting = max(dot(fs_in.normal, fs_in.sunDirection), 0.01); //0.0

   color = vec4(diffuse * lighting, 1.0);
}