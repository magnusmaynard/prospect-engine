﻿#version 450

layout (vertices = 4) out;

uniform int nodeLevel;
uniform ivec4 nodeEdgeScaling;

in VS_OUT
{
   vec2 textureCoord;
} tcs_in[];

out TCS_OUT
{
   vec2 textureCoord;
} tcs_out[];

void main()
{
   if(gl_InvocationID == 0)
   {
      //TODO: http://victorbush.com/2015/01/tessellated-terrain/
      //https://bitbucket.org/victorbush/ufl.cap5705.terrain/src/93c5ab3824a5a66d87d1bb6dcc9ed9aee7a16357/src_uniform/shader/tess.tcs.glsl?at=master&fileviewer=file-view-default

      float tessLevel = 8;
      gl_TessLevelOuter[0] = tessLevel * nodeEdgeScaling[0];
      gl_TessLevelOuter[1] = tessLevel * nodeEdgeScaling[3];
      gl_TessLevelOuter[2] = tessLevel * nodeEdgeScaling[1];
      gl_TessLevelOuter[3] = tessLevel * nodeEdgeScaling[2];;
      gl_TessLevelInner[0] = tessLevel;
      gl_TessLevelInner[1] = tessLevel;
   }

   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
   tcs_out[gl_InvocationID].textureCoord = tcs_in[gl_InvocationID].textureCoord;
}