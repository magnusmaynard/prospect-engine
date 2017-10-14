#version 450

layout (location = 0) uniform mat4 projection;
layout (location = 2) uniform mat4 model;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoords;

out vec2 textureCoord;

void main()
{
   textureCoord = textureCoords;

   gl_Position = projection * model * vec4(position, 0, 1);
}
