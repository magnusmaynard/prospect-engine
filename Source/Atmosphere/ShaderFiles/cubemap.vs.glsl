#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
   vec3 textureCoord;
} vs_out;

void main()
{
   vec3[4] verticies = vec3[4](
      vec3(-1, -1, 1),
      vec3(1, -1, 1),
      vec3(-1, 1, 1),
      vec3(1, 1, 1));

   vs_out.textureCoord = mat3(view) * verticies[gl_VertexID];

   gl_Position = vec4(verticies[gl_VertexID], 1.0);
}
