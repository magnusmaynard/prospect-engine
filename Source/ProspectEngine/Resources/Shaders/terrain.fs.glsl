#version 450

layout (binding = 0) uniform sampler2D textureHeight;

uniform float minHeight;
uniform float maxHeight;

layout (std140, binding = 1) uniform NodeUniforms
{
   vec4 Origin;
   ivec4 Edges;
   float Size;
   float Level;
} node;

out vec4 color;

in TES_OUT
{
   vec2 textureCoord;
} fs_in;

void main()
{
   //float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x * maxHeight;
   //float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x * maxHeight;
   //float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x * maxHeight;
   //float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x * maxHeight;
   //vec3 va = normalize(vec3(2.0, 0, xPos - xNeg));
   //vec3 vb = normalize(vec3(0, 2.0, yPos - yNeg));

   //vec3 normal = vec3(cross(va, vb));

   //vec3 lightDirection = vec3(1, 1, 1);

   //float lighting = max(dot(normal, lightDirection), 0.0);

   //vec3 diffuse = vec3(0.3, 0.3, 0.3) * lighting; //TODO: uncomment.
   //color = vec4(diffuse, 1.0);


   float diffuse = texture(textureHeight, fs_in.textureCoord).r;
   color = vec4(diffuse, diffuse, diffuse, 1.0);

//float dis = node.Level / 8.0;
//   color = vec4(dis, dis, dis, 1.0);
}