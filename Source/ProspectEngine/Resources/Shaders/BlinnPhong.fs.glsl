#version 450

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 DiffuseColor;
   float Brightness;
} light;

struct Material
{
   vec4 Diffuse;
   vec4 Ambient;
   vec4 SpecularAndPower;
};

layout (std140) uniform MaterialUniforms
{
   Material Materials[10];
} materials;

layout (location = 100) uniform int MaterialID; 

in VS_OUT
{
   smooth vec3 N;
   smooth vec3 L;
   smooth vec3 V;
} fs_in;

out vec4 color;

void main()
{
   Material material = materials.Materials[MaterialID];

   vec3 N = normalize(fs_in.N);
   vec3 L = normalize(fs_in.L);
   vec3 V = normalize(fs_in.V);
   vec3 H = normalize(L + V); //TODO: H?
   
   vec3 ambient = material.Ambient.xyz;
   vec3 diffuse = max(dot(N, L), 0.0) * material.Diffuse.xyz * light.Brightness;

   float specularPower = material.SpecularAndPower.w;
   vec3 specular = vec3(0, 0, 0);// pow(max(dot(N, H), 0.0), specularPower * 1.0) * material.SpecularAndPower.xyz;

   color = vec4(ambient + specular + diffuse, 1.0);
}