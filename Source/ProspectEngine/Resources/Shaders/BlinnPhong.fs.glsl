#version 450

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 Color;
   vec4 Brightness;
} light;

layout (std140) uniform EntityUniforms
{
   mat4 Model;
   mat4 Normal;
   ivec4 MaterialID;
} entity;

struct Material
{
   vec4 Diffuse;
   vec4 Ambient;
   vec4 SpecularAndPower;
};

layout (std140) uniform MaterialLibraryUniforms
{
   Material Materials[10];
} materialLibrary;

in VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} fs_in;

out vec4 color;

Material material = materialLibrary.Materials[entity.MaterialID.x];
vec3 ambientAlbedo = material.Ambient.xyz;
vec3 diffuseAlbedo = material.Diffuse.xyz;
vec3 specularAlbedo = material.SpecularAndPower.xyz;
float specularPower = material.SpecularAndPower.w;
float brightness = light.Brightness.x;

void main()
{
   vec3 N = normalize(fs_in.N);
   vec3 L = normalize(fs_in.L);
   vec3 V = normalize(fs_in.V);
   vec3 H = normalize(L + V);

   vec3 ambient = ambientAlbedo;
   vec3 diffuse = diffuseAlbedo * max(dot(N, L), 0) * brightness;
   vec3 specular = specularAlbedo * pow(max(dot(N, H), 0.0), specularPower) * brightness;

   color = vec4(ambient + diffuse + specular, 1);
}