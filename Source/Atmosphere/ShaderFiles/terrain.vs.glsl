#version 450

layout (location = 0) in vec3 point;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (binding = 0) uniform sampler2D textureHeight;//TEMP

out VS_OUT
{
   vec2 textureCoord;
} vs_out;

void main()
{

   const float size = 1000.0;
   //vs_out.textureCoord = point.xy / size + vec2(0.5);
   vs_out.textureCoord = point.xy / 1000.0 + vec2(0.5);

   //float height =  texture(textureHeight, vs_out.textureCoord).r * 1000.0; //TEMP

   //float cellSize = 1000.0;
   // float textureOffset = 0.5 * cellSize; //offset by half a cell
   // vec4 texel = texture(textureHeight, vec2(point.x + textureOffset, point.z + textureOffset) / (textureSize(textureHeight, 0) * cellSize));

   //gl_Position = vec4(point.xy, point.z, 1.0);



   //gl_Position = projection * view * model * vec4(point, 1.0);


   gl_Position = vec4(point, 1.0);
}
