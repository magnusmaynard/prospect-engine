#version 450

layout (location = 0) in vec3 point;

uniform float size;

//Node properties
uniform vec3 nodeOrigin;
uniform vec3 nodeNormal;
uniform vec3 nodeLeft;
uniform vec3 nodeTop;
uniform float nodeSize;

out VS_OUT
{
   vec2 textureCoord;
} vs_out;

void main()
{
   float halfSize = nodeSize * 0.5;

   const vec3 offsets[] = vec3[](
      nodeLeft * -halfSize + nodeTop * halfSize,
      nodeLeft * halfSize + nodeTop * halfSize,
      nodeLeft * -halfSize + nodeTop * -halfSize,
      nodeLeft * halfSize + nodeTop * -halfSize);

   const vec3 vertex = nodeOrigin + offsets[gl_VertexID];

   const vec2 tc = vec2(dot(nodeLeft, vertex), dot(nodeTop, vertex));

   vs_out.textureCoord = tc / size + vec2(0.5);

   gl_Position = vec4(vertex, 1.0);
}