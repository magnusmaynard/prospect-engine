#version 450

layout (quads, fractional_odd_spacing) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float radius;
uniform vec3 origin;

//uniform sampler2D textureHeight;
layout (binding = 0) uniform sampler2D textureHeight;//TEMP

in TCS_OUT
{
   vec2 textureCoord;
} tes_in[];

out TES_OUT
{
   vec2 textureCoord;
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

   //p.z += texture(textureHeight, tc).r; //TODO: ununcomment this.

   //gl_Position = p;
   gl_Position = projection * view * model * vec4(normalize(p.xyz - origin) * radius, 1.0);
   tes_out.textureCoord = tc;
}
