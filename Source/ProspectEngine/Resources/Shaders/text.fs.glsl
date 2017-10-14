#version 450

uniform sampler2D sampler; 

out vec4 color;


in vec2 textureCoord;

void main()
{
   float value = texture(sampler, textureCoord).x;
   color = vec4(value, value, value, value);
}