#version 450

layout (location = 0) in vec3 point;

layout (std140, binding = 0) uniform CameraUniforms
{
   mat4 Projection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140, binding = 4) uniform NodeUniforms //TODO: Automatic binding index.
{
   vec4 Origin;
   ivec4 Edges;
   float Size;
   float Level;
} node;

uniform float totalSize;

out VS_OUT
{
   vec2 textureCoord;
} vs_out;

void main()
{
   //float halfSize = node.Size * 0.5;
   float halfSize = node.Size * 0.5;

   const vec3 vertices[] = vec3[](
      node.Origin.xyz + vec3(-halfSize, 0, halfSize),
      node.Origin.xyz + vec3( halfSize, 0, halfSize),
      node.Origin.xyz + vec3(-halfSize, 0, -halfSize),
      node.Origin.xyz + vec3( halfSize, 0, -halfSize));

   const vec4 vertex = vec4(vertices[gl_VertexID], 1.0);

   vs_out.textureCoord = vertex.xz / totalSize + vec2(0.5);

   gl_Position = camera.Projection * camera.View * vertex;
}
