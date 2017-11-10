#version 450

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 DiffuseColor;
} light;

layout (location = 5) uniform vec4 diffuse;

in VS_OUT
{
   vec3 Normal;
} vs_in;

out vec4 color;

void main()
{
   float power = max(dot(vs_in.Normal, -light.Direction.xyz), 0.0) * 1.8;

   color = vec4(diffuse.xyz * power, 1);
   //color = vec4(light.Direction.xyz, 1);
}