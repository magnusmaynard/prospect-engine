#version 450

layout (binding = 0) uniform samplerCube cubeMap;

out vec4 color;

in VS_OUT
{
   vec3 textureCoord;
} fs_in;


void main()
{
   color = texture(cubeMap, fs_in.textureCoord);
}