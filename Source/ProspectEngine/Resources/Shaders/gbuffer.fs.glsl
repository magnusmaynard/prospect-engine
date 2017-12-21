#version 450

layout (binding = 0) uniform sampler2D gBuffer0;

in VS_OUT
{
   vec2 textureCoords;
} fs_in;

out vec4 color;

void main()
{
   color = texelFetch(gBuffer0, ivec2(fs_in.textureCoords), 0);
}
