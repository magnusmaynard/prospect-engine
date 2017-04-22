#version 450

layout (vertices = 4) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   if(gl_InvocationID == 0)
   {
      gl_TessLevelInner[0] = 8.0;
      gl_TessLevelInner[1] = 8.0;
      gl_TessLevelOuter[0] = 2.0;
      gl_TessLevelOuter[1] = 2.0;
      gl_TessLevelOuter[2] = 2.0;
      gl_TessLevelOuter[3] = 2.0;
   }

   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

   //gl_Position = projection * view * model * vec4(point, 1.0);
}
