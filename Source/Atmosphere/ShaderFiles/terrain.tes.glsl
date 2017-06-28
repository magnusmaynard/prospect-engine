#version 450

layout (quads, equal_spacing) in;

layout (binding = 0) uniform sampler2D textureHeight;

in TCS_OUT
{
   vec2 textureCoord;
} tes_in[];

out TES_OUT
{
   vec2 textureCoord;
   vec3 normal;
} tes_out;

void main()
{
   vec2 tc1 = mix(tes_in[0].textureCoord, tes_in[1].textureCoord, gl_TessCoord.x);
   vec2 tc2 = mix(tes_in[2].textureCoord, tes_in[3].textureCoord, gl_TessCoord.x);
   vec2 tc = mix(tc2, tc1, gl_TessCoord.y);

   tes_out.textureCoord = tc;

   vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
   vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);

   vec4 p = mix(p2, p1, gl_TessCoord.y);

   p.y += texture(textureHeight, tes_out.textureCoord).r;

   ////Compute normals
   //float xNeg = textureOffset(textureHeight, tes_out.textureCoord, ivec2(-1, 0)).x;
   //float xPos = textureOffset(textureHeight, tes_out.textureCoord, ivec2( 1, 0)).x;
   //float yNeg = textureOffset(textureHeight, tes_out.textureCoord, ivec2( 0,-1)).x;
   //float yPos = textureOffset(textureHeight, tes_out.textureCoord, ivec2( 0, 1)).x;
   //vec3 va = normalize(vec3(2.0, 0, xPos - xNeg));
   //vec3 vb = normalize(vec3(0, 2.0, yPos - yNeg));

   //tes_out.normal = vec3(cross(va, vb));

   gl_Position = p;
}
