#version 450

layout (binding = 0) uniform sampler2D textureHeight;

out vec4 color;

in TES_OUT
{
   vec2 textureCoord;
   vec3 normal;
} fs_in;

void main()
{
   float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x;
   float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x;
   float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x;
   float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x;
   vec3 va = normalize(vec3(2.0, 0, xPos - xNeg));
   vec3 vb = normalize(vec3(0, 2.0, yPos - yNeg));

   vec3 normal = vec3(cross(va, vb));

   vec3 lightDirection = vec3(1, 1, 1);

   float lighting = max(dot(normal, lightDirection), 0.0);

   vec3 diffuse = vec3(0.5, 0.5, 0.5) * lighting;

   color = vec4(diffuse, 1.0);
}