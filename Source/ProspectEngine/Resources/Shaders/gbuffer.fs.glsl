#version 450

layout (binding = 0) uniform sampler2D albedoTexture;
layout (binding = 1) uniform sampler2D normalTexture;
layout (binding = 2) uniform sampler2D specularTexture;
layout (binding = 3) uniform sampler2D depthTexture;

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
   vec2 textureCoords;
} fs_in;

out vec4 color;

vec3 CalculateLighting(Material material, vec3 N, vec3 V)
{
   //Extract material info
   vec3 ambientAlbedo = material.Ambient.xyz;
   vec3 diffuseAlbedo = material.Diffuse.xyz;
   vec3 specularAlbedo = material.SpecularAndPower.xyz;
   float specularPower = material.SpecularAndPower.w;

   //Apply all lights.
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

// float GetLinearDepth()
// {
//    vec2 uv = fs_in.textureCoords;
//    float zNear = 0.01;    // TODO: Replace by the zNear of your perspective projection
//    float zFar  = 10000.0; // TODO: Replace by the zFar  of your perspective projection
//    float depth = texture2D(depthTexture, uv).x;

//    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
// }

vec3 CalculateViewPosition(float depth, vec2 screenPosition)
{
    //Scale position from 0.0 to 1.0 to -1.0 to 1.0 range.
    vec4 projectedPosition;
    projectedPosition.xy = vec3(screenPosition * 2.0 - 1.0;
    projectedPosition.z = depth * 2.0 - 1.0;
    projectedPosition.w = 1.0;

    vec4 viewPosition = inverse(camera.PerspectiveProjection) * projectedPosition;
    return viewPosition.xyz / viewPosition.w;
}

void main()
{
   vec4 albedo = texture(albedoTexture, fs_in.textureCoords);
   vec4 normal = texture(normalTexture, fs_in.textureCoords);
   float depth = texture(depthTexture, fs_in.textureCoords).r;
   vec3 position = CalculateViewPosition(depth, fs_in.textureCoords);

   int materialID = int(albedo.w);
   Material material = materialLibrary.Materials[materialID];


   vec3 P = normalize(position.xyz);
   vec3 V = -P;
   vec3 N = normalize(normal.xyz);

   color = vec4(CalculateLighting(material, N, V), 0);
}
