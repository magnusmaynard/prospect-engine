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
   vec4 Position;
   vec4 Direction;
   vec4 ColorAndBrightness;
   vec4 RangeAndAngleAndType;
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

//Get buffer value from texture.
vec4 albedoBuffer = texture(albedoTexture, fs_in.textureCoords);
vec4 normalBuffer = texture(normalTexture, fs_in.textureCoords);
vec4 specularBuffer = texture(specularTexture, fs_in.textureCoords);
vec4 depthBuffer = texture(depthTexture, fs_in.textureCoords);

//Extract data from buffers.
vec3 diffuseAlbedo = albedoBuffer.rgb;
vec3 normal = normalBuffer.xyz;
float viewDependentRoughness = normalBuffer.a;
float specularPower = specularBuffer.r;
float specularIntensity = specularBuffer.g;
int materialID = int(specularBuffer.b);
float SSSTranslucency = specularBuffer.a;
vec3 specularAlbedo = diffuseAlbedo * specularIntensity;
float depth = depthBuffer.x;

out vec4 color;

vec3 CalculateDirectionalLight(Light light, vec3 V, vec3 N)
{
    vec3 lightColor = light.ColorAndBrightness.rgb;
    float lightBrightness = light.ColorAndBrightness.a;

    vec3 L = normalize(mat3(camera.View) * -light.Direction.xyz);
    vec3 H = normalize(L + V); //Half vector

    vec3 diffuse = diffuseAlbedo * max(dot(N, L), 0) * lightBrightness;
    vec3 specular = specularAlbedo * pow(max(dot(N, H), 0.0), specularPower) * lightBrightness;

    return diffuse + specular;
}

vec3 CalculatePointLight(Light light, vec3 position, vec3 V, vec3 N)
{
    vec3 lightPosition = (camera.View * vec4(light.Position.xyz, 1)).xyz;
    vec3 lightVector = lightPosition - position;
    float distance = length(lightVector);

    vec3 lightColor = light.ColorAndBrightness.rgb;
    float lightBrightness = light.ColorAndBrightness.a;
    float lightRange = light.RangeAndAngleAndType.r;

    float attenuation =  pow(max(0, 1 - (distance * distance) / (lightRange * lightRange)), 2);

    vec3 L = normalize(lightVector);
    vec3 H = normalize(L + V); //Half vector

    vec3 diffuse = diffuseAlbedo * max(dot(N, L), 0) * lightBrightness;
    vec3 specular = specularAlbedo * pow(max(dot(N, H), 0.0), specularPower) * lightBrightness;

    return (diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight()
{
   return vec3(0);
}

vec3 CalculateLighting(vec3 position)
{
   vec3 P = normalize(position);
   vec3 V = -P;
   vec3 N = normalize(normal);

   //Apply all lights.
   vec3 lightingTotal;
   for(int i = 0; i < lights.Count; i++)
   {
      Light light = lights.Lights[i];
      int lightType = int(light.RangeAndAngleAndType.z);

      //Directional
      if(lightType == 0)
      {
          lightingTotal += CalculateDirectionalLight(light, V, N);
      }
      //Point
      else if(lightType == 1)
      {
         lightingTotal += CalculatePointLight(light, position, V, N);
      }
      //Spot
      else
      {
         //TODO:
      }

    //TODO: add ambient light.
    //   bool isAmbientLightSource = i == 0;//TODO: store in Light uniform.
    //   if(isAmbientLightSource)
    //   {
    //      vec3 ambient = vec3(0.1, 0.1, 0.1);
    //      lightingTotal += ambient;
    //   }
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

//Calculates a position in view space from a depth and a position on the screen.
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
    vec3 position = CalculateViewSpacePosition(depth, fs_in.textureCoords);

    if(materialID < 0)
    {
        color = vec4(diffuseAlbedo, 1);
    }
    else
    {
        color = vec4(CalculateLighting(position), 1);
    }
}
