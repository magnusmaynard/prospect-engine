#version 450

layout (binding = 0) uniform sampler2D textureHeight;

uniform float minHeight;
uniform float maxHeight;

layout (std140, binding = 1) uniform DirectionalLightUniforms
{
   vec4 Direction;
} light;

layout (std140, binding = 4) uniform NodeUniforms //TODO: Automatic binding index.
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
   float xNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2(-1, 0)).x * maxHeight;
   float xPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 1, 0)).x * maxHeight;
   float yNeg = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0,-1)).x * maxHeight;
   float yPos = textureOffset(textureHeight, fs_in.textureCoord, ivec2( 0, 1)).x * maxHeight;
   vec3 va = normalize(vec3(2.0, xPos - xNeg, 0));
   vec3 vb = normalize(vec3(0, yPos - yNeg, 2.0));

   vec3 normal = vec3(cross(va, vb));

   vec3 lightDirection = light.Direction.xyz;

   float lighting = max(dot(normal, lightDirection), 0.0) * 1.8;

   float height = texture(textureHeight, fs_in.textureCoord).r * 0.2;
   vec3 diffuse = vec3(0.1 + height);
   vec3 ambient = vec3(0.05);

   color = vec4(diffuse * lighting + ambient, 1.0);
}