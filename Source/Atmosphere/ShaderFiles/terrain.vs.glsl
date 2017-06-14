#version 450

layout (location = 0) in vec3 point;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 origin;
uniform float size;
uniform float nodeSize;

out VS_OUT
{
   vec2 textureCoord;
} vs_out;

void main()
{
   float halfSize = nodeSize * 0.5;

   const vec3 vertices[] = vec3[](
      origin + vec3(-halfSize, 0, halfSize),
      origin + vec3( halfSize, 0, halfSize),
      origin + vec3(-halfSize, 0, -halfSize),
      origin + vec3( halfSize, 0, -halfSize));

   const vec4 vert = vec4(vertices[gl_VertexID], 1.0);

   vs_out.textureCoord = vert.xz / size + vec2(0.5);

   gl_Position = projection * view * model * vert;
}
