#version 450

out VS_OUT
{
   vec2 textureCoords;
} vs_out;

void main()
{
   const vec4 vertices[4] = vec4[4](
      vec4(-1, +1, -1, 1),
      vec4(-1, -1, -1, 1),
      vec4(+1, +1, -1, 1),
      vec4(+1, -1, -1, 1));

   const vec2 textureCoords[4] = vec2[4](
      vec2(0, 1),
      vec2(0, 0),
      vec2(1, 1),
      vec2(1, 0));

   gl_Position = vertices[gl_VertexID];
   vs_out.textureCoords = textureCoords[gl_VertexID];
}