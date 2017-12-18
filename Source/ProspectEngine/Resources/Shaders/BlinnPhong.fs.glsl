#version 450

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 ViewDirection;
   vec4 Position;
   vec2 ScreenSize;
} camera;

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

layout (std140) uniform EntityUniforms
{
   mat4 Model;
   mat4 Normal;
   ivec4 MaterialID;
} entity;

in VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} fs_in;

out vec4 color;

Material material = materials.Materials[entity.MaterialID.x];
vec3 ambientAlbedo = material.Ambient.xyz;
vec3 diffuseAlbedo = material.Diffuse.xyz;
vec3 specularAlbedo = material.SpecularAndPower.xyz;
float specularPower = material.SpecularAndPower.w;

void main()
{
   vec3 N = normalize(fs_in.N);
   vec3 L = normalize(fs_in.L);
   vec3 V = normalize(fs_in.V);
   vec3 R = reflect(-L, N);

   vec3 ambient = ambientAlbedo;
   vec3 diffuse = diffuseAlbedo * max(dot(N, L), 0);
   vec3 specular = pow(max(dot(R, V), 0.0), specularPower) * specularAlbedo;

   color = vec4(ambient + diffuse + specular, 1);
}