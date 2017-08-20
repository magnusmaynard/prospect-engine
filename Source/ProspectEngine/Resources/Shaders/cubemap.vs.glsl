#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (binding = 0) uniform samplerCube cubeMap;

out VS_OUT
{
   vec3 textureCoord;
} vs_out;

void main()
{
   vec3 origin = vec3(0, 0, 0);

   vec3[6] points = vec3[6](
      vec3( 1, -1, -1),
      vec3(-1, -1, -1),
      vec3( 1,  1, -1),

      vec3(-1,  1, -1),
      vec3( 1,  1, -1),
      vec3(-1, -1, -1));

   vec3 dir = normalize(points[gl_VertexID] - origin);

   gl_Position = projection * view * model * vec4(dir, 1.0);

   //vec4 p = projection * view * model * points[gl_VertexID];

   vs_out.textureCoord = mat3(view) * points[gl_VertexID].xyz;


   //color = texture(cubeMap, fs_in.textureCoord);

   //gl_Position = p;
}
