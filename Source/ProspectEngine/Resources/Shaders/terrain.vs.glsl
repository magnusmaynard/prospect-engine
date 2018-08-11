#version 450

layout (location = 0) in vec3 point;

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   mat4 InverseView;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform NodeUniforms
{
   vec4 Origin;
   ivec4 Edges;
   float Size;
   float Level;
} node;

layout (std140) uniform TerrainUniforms
{
   uint MaterialID;
   float MinHeight;
   float MaxHeight;
   float TotalSize;
} terrain;

out VS_OUT
{
   vec2 textureCoord;
} vs_out;

void main()
{
   float halfSize = node.Size * 0.5;

   const vec3 vertices[] = vec3[](
      node.Origin.xyz + vec3(+halfSize, 0, +halfSize),
      node.Origin.xyz + vec3(-halfSize, 0, +halfSize),
      node.Origin.xyz + vec3(+halfSize, 0, -halfSize),
      node.Origin.xyz + vec3(-halfSize, 0, -halfSize));

   const vec4 vertex = vec4(vertices[gl_VertexID], 1.0);

   vs_out.textureCoord = vertex.xz / terrain.TotalSize + vec2(0.5);

   gl_Position = vertex;
}
