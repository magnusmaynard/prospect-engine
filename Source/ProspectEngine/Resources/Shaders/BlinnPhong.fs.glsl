#version 450

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 DiffuseColor;
   vec4 Brightness;
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

//TODO: Currently just uses Phong, make Blinn-phong.
void main()
{
   Material material = materials.Materials[MaterialID];

   vec3 N = normalize(fs_in.N);
   vec3 L = normalize(fs_in.L);
   vec3 V = normalize(fs_in.V);

   vec3 R = reflect(-L, N);
   
   vec3 ambient = material.Ambient.xyz;
   vec3 diffuseAlbedo = material.Diffuse.xyz;
   vec3 diffuse = max(dot(N, L), 0.0) * diffuseAlbedo * light.Brightness.x;

   vec3 specularAlbedo =  material.SpecularAndPower.xyz;
   float specularPower = material.SpecularAndPower.w;
   vec3 specular = pow(max(dot(R, V), 0.0), specularPower) * specularAlbedo;

   color = vec4(ambient + diffuse + specular, 1.0);
}