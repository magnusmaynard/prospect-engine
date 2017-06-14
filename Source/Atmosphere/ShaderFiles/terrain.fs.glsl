#version 450

layout (binding = 0) uniform sampler2D textureHeight;

out vec4 color;

in TES_OUT
{
   vec2 textureCoord;
} fs_in;


void main()
{
   //float height =  texture(textureHeight, fs_in.textureCoord).r; //TEMP

   vec3 diffuse = vec3(1.0, 0.1, 0.1);

   color = vec4(diffuse, 1.0);
}