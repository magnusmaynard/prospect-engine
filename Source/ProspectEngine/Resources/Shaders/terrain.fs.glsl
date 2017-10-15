#version 450

layout (binding = 0) uniform sampler2D textureHeight;

uniform float heightScale;

out vec4 color;

in TES_OUT
{
   vec2 textureCoord;
} fs_in;

void main()
{
   float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x * heightScale;
   float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x * heightScale;
   float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x * heightScale;
   float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x * heightScale;
   vec3 va = normalize(vec3(2.0, 0, xPos - xNeg));
   vec3 vb = normalize(vec3(0, 2.0, yPos - yNeg));

   vec3 normal = vec3(cross(va, vb));

   vec3 lightDirection = vec3(1, 1, 1);

   float lighting = max(dot(normal, lightDirection), 0.0);

   vec3 diffuse = vec3(0.3, 0.3, 0.3) * lighting; //TODO: uncomment.

   color = vec4(diffuse, 1.0);

   //color = vec4(fs_in.textureCoord, 0.0, 1.0);
   //color = vec4(texture(textureHeight, fs_in.textureCoord).r * 0.1, 0.1, 0.1, 1); //TODO: uncomment this.
}