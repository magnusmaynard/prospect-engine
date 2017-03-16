#version 450

uniform mat4 view;
uniform mat4 projection;

void main()
{
   const vec4 vertices[6] = vec4[6](
      vec4(-10.0, -0.2, 10.0, 1.0),
      vec4(10.0, -0.2, 10.0, 1.0),
      vec4(-10.0, -0.2, -10.0, 1.0),
      vec4(10.0, -0.2, 10.0, 1.0),
      vec4(10.0, -0.2, -10.0, 1.0),
      vec4(-10.0, -0.2, -10.0, 1.0));


   gl_Position = projection * view * vertices[gl_VertexID];
}
