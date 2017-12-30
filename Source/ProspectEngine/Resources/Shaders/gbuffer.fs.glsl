#version 450

layout (binding = 0) uniform sampler2D albedoTexture;
layout (binding = 1) uniform sampler2D normalTexture;
layout (binding = 2) uniform sampler2D specularTexture;
layout (binding = 3) uniform sampler2D depthTexture;

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
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

vec3 CalculateLighting(vec3 position, vec4 albedo, vec4 normal, vec4 specular)
{
   //Extract data from buffers.
   vec3 diffuseAlbedo = albedo.rgb;
   float specularPower = specular.r;
   float specularIntensity = specular.g;
   vec3 specularAlbedo = diffuseAlbedo * specularIntensity;

   vec3 P = normalize(position.xyz);
   vec3 V = -P;
   vec3 N = normalize(normal.xyz);

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

//Calculates a position is view space from a depth and a position on the screen.
vec3 CalculateViewSpacePosition(float depth, vec2 screenPosition)
{
    //Scale position from 0.0 to 1.0 to -1.0 to 1.0 range.
    vec3 clipSpacePosition = vec3(screenPosition, depth) * 2 - vec3(1);

    //Transform the position to view space.
    vec4 viewSpacePosition = camera.InversePerspectiveProjection * vec4(clipSpacePosition, 1);

    return viewSpacePosition.xyz / viewSpacePosition.w;
}

void main()
{
   vec4 albedo = texture(albedoTexture, fs_in.textureCoords);
   vec4 normal = texture(normalTexture, fs_in.textureCoords);
   vec4 specular = texture(specularTexture, fs_in.textureCoords);
   float depth = texture(depthTexture, fs_in.textureCoords).r;

   vec3 position = CalculateViewSpacePosition(depth, fs_in.textureCoords);

   color = vec4(CalculateLighting(position, albedo, normal, specular), 1);
}
