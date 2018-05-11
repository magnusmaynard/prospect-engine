#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

layout (binding = 0) uniform sampler2D heightMapTexture;

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   mat4 InverseView;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform TerrainUniforms
{
   float MinHeight;
   float MaxHeight;
   float TotalSize;
   float Null;
} terrain;

// layout (std140) uniform GrassUniforms
// {
//    float PatchSize;
// } grass;

in VS_OUT
{
   int Lod;
   int MaxLevels;
   float BladeCountMultiplier;
} gs_in[];

out GS_OUT
{
   vec3 Normal;
} gs_out;

//https://stackoverflow.com/a/28095165/3209889
float GoldNoise(in vec2 coordinate, in float seed)
{
    const float PHI = 1.61803398874989484820459 * 00000.1; // Golden Ratio
    const float PI  = 3.14159265358979323846264 * 00000.1; // PI
    const float SQ2 = 1.41421356237309504880169 * 10000.0; // Square Root of Two

    return fract(sin(dot(coordinate*(seed+PHI), vec2(PHI, PI)))*SQ2);
}

void OutputVertex(vec3 vertex)
{
   gl_Position = camera.PerspectiveProjection * camera.View * vec4(vertex, 1);
   EmitVertex();
}

vec3 RandomDirection(float seed)
{
    return normalize(
        vec3(
            GoldNoise(gl_in[0].gl_Position.xz, 1 + seed), 0, GoldNoise(gl_in[0].gl_Position.xz, 7 + seed)) -
            vec3(0.5, 0, 0.5));
}

float RandomRange(float min, float max, float seed)
{
    return mix(min, max, GoldNoise(gl_in[0].gl_Position.xz, 45 + seed));
}

//#define DEBUG


void main()
{
   // if(gs_in[0].Lod > 3) //TODO:
   // {
   //    return;
   // }

#ifdef DEBUG
    //Constants
    float minLength = 2.0;//0.5;
    float maxLength = 2.0;//2.0;
    float minWidth = 0.2;//0.02;
    float maxWidth = 0.2;//0.05;
    float minAngle = 0.00;
    float maxAngle = 0.1;
   float taperFactor = 1.0;//0.9;
   float sectionSpacing = 0.3;
   int maxBladeCount = 1;//6;
   float bladeRadius = 0.0;//0.3;
#endif
#ifndef DEBUG
    //Constants
    float minLength = 0.5;
    float maxLength = 2.0;
    float minWidth = 0.02;
    float maxWidth = 0.05;
    float minAngle = 0.00;
    float maxAngle = 0.1;
   float taperFactor = 0.9;
   float sectionSpacing = 0.3;
   int maxBladeCount = 6;
   float bladeRadius = 0.3;
#endif


   int bladeCount = int(maxBladeCount * gs_in[0].BladeCountMultiplier);

   for(int b = 0; b < bladeCount; b++)
   {
      float length = RandomRange(minLength, maxLength, b);
      float width = RandomRange(minWidth, maxWidth, b);
      vec3 direction = RandomDirection(b);
      float angle = RandomRange(minAngle, maxAngle, b);

      int sectionCount = int(length / sectionSpacing);
      vec3 up = vec3(0, 1, 0);
      vec3 sideDirection = cross(direction, up);
      vec3 side = sideDirection * width;

      vec3 basePosition = gl_in[0].gl_Position.xyz + direction * bladeRadius;

      vec2 textureCoord = basePosition.xz / terrain.TotalSize + vec2(0.5);
      float height = 0.0;// texture(heightMapTexture, textureCoord).x * terrain.MaxHeight;
      basePosition.y = height;

      vec3 previousPosition = basePosition;
      float taper = 1;

      for(int i = 0; i < sectionCount; i++)
      {
         vec3 sectionPosition = previousPosition + mix(up, direction, angle) * sectionSpacing;


        gs_out.Normal = normalize(cross(sectionPosition - previousPosition, sideDirection));

         angle += 0.1;//TODO:

         taper = taper * taperFactor;
         vec3 taperedSide = side * taper;
         OutputVertex(sectionPosition + taperedSide);
         OutputVertex(sectionPosition - taperedSide);

         previousPosition = sectionPosition;
      }

      vec3 endPosition = mix(up, direction, angle) * sectionSpacing;
      OutputVertex(previousPosition + endPosition);

      EndPrimitive();
   }
}