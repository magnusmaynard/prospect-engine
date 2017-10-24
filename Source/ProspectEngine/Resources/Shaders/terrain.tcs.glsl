#version 450

layout (vertices = 4) out;

layout (std140) uniform NodeUniforms //TODO: Automatic binding index.
{
   vec4 Origin; //xyz
   ivec4 Edges;
   float Size;
   float Level;
} node;

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

      float tessLevel = 4;
      gl_TessLevelOuter[0] = tessLevel * node.Edges.x;
      gl_TessLevelOuter[1] = tessLevel * node.Edges.w;
      gl_TessLevelOuter[2] = tessLevel * node.Edges.y;
      gl_TessLevelOuter[3] = tessLevel * node.Edges.z;
      gl_TessLevelInner[0] = tessLevel;
      gl_TessLevelInner[1] = tessLevel;
   }

   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
   tcs_out[gl_InvocationID].textureCoord = tcs_in[gl_InvocationID].textureCoord;
}
