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

struct Light
{
   vec4 Direction;
   vec4 Color;
   vec4 Brightness;
};

layout (std140) uniform LightsUniforms
{
   Light Lights[10];
   int Count;
} lights;

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
   vec3 V;
} fs_in;

layout (std140) uniform EntityUniforms
{
   mat4 Model;
   mat4 Normal;
   ivec4 MaterialID;
} entity;

layout (location = 0) out vec4 color0;

Material material = materialLibrary.Materials[entity.MaterialID.x];
vec3 ambientAlbedo = material.Ambient.xyz;
vec3 diffuseAlbedo = material.Diffuse.xyz;
vec3 specularAlbedo = material.SpecularAndPower.xyz;
float specularPower = material.SpecularAndPower.w;

vec3 N = normalize(fs_in.N);
vec3 V = normalize(fs_in.V);

vec3 CalculateLighting()
{
   vec3 lightingTotal;
   for(int i = 0; i < lights.Count; i++)
   {
      Light light = lights.Lights[i];
      vec3 L = normalize(mat3(camera.View) * -light.Direction.xyz);
      vec3 H = normalize(L + V);

      vec3 diffuse = diffuseAlbedo * max(dot(N, L), 0) * light.Brightness.x;
      vec3 specular = specularAlbedo * pow(max(dot(N, H), 0.0), specularPower) * light.Brightness.x;

      lightingTotal += diffuse + specular;
   }

   return lightingTotal;
}

void main()
{
   vec3 ambient = ambientAlbedo;
   vec3 lighting = CalculateLighting();

   color0 = vec4(ambient + lighting, 1);
}