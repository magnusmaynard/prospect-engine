#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

layout(binding = 0) uniform sampler2D heightMapTexture;

layout(std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   mat4 InverseView;
   vec4 Position;
   vec2 ScreenSize;
}
camera;

layout(std140) uniform TerrainUniforms
{
   float MinHeight;
   float MaxHeight;
   float TotalSize;
   float Null;
}
terrain;

layout (std140) uniform GrassUniforms
{
   bool FrontFacing;
} grass;

in VS_OUT
{
   int Lod;
   int LodMax;
}
gs_in[];

out GS_OUT
{
   vec3 Normal;
   vec3 InverseNormal;
}
gs_out;

// https://stackoverflow.com/a/28095165/3209889
float GoldNoise(in vec2 coordinate, in float seed)
{
   const float PHI = 1.61803398874989484820459 * 00000.1; // Golden Ratio
   const float PI = 3.14159265358979323846264 * 00000.1;  // PI
   const float SQ2 = 1.41421356237309504880169 * 10000.0; // Square Root of Two

   return fract(sin(dot(coordinate * (seed + PHI), vec2(PHI, PI))) * SQ2);
}

float RandomRange(float min, float max, float seed)
{
   return mix(min, max, GoldNoise(gl_in[0].gl_Position.xz, 45 + seed));
}

vec3 RandomDirection(float seed)
{
   return normalize(vec3(GoldNoise(gl_in[0].gl_Position.xz, 1 + seed), 0,
                        GoldNoise(gl_in[0].gl_Position.xz, 7 + seed)) -
                    vec3(0.5, 0, 0.5));
}

void OutputVertex(vec3 vertex)
{
   gl_Position = camera.PerspectiveProjection * camera.View * vec4(vertex, 1);
   EmitVertex();
}

void OutputNormal(vec3 normal)
{
   gs_out.Normal =  mat3(camera.View) * normal;
   gs_out.InverseNormal =  mat3(camera.View) * -normal;
}

void main()
{
   int lod = gs_in[0].Lod;

   if(lod > gs_in[0].LodMax || lod < 0)
   {
      return;
   }

   // Constants varying with lods.
   const float maxLengthLods[] = float[]( 2.0, 1.8, 1.2, 0.6 );
   const float minWidthLods[] = float[]( 0.02, 0.03, 0.04, 0.06 );
   const float maxWidthLods[] = float[]( 0.05, 0.06, 0.10, 0.14 );
   const int bladeCountLods[] = int[]( 6, 4, 3, 2 );

    // Constants
   float minLength = 0.5;
   float maxLength = maxLengthLods[lod];
   float minWidth = minWidthLods[lod];
   float maxWidth = maxWidthLods[lod];
   float minAngle = 0.00;
   float maxAngle = 0.1;
   float taperFactor = 0.9;
   float sectionSpacing = 0.4;
   float bladeRadius = 0.3;
   int bladeCount = bladeCountLods[lod];

   for (int b = 0; b < bladeCount; b++)
   {
      //Randomise.
      float length = RandomRange(minLength, maxLength, b);
      float width = RandomRange(minWidth, maxWidth, b);
      vec3 direction = RandomDirection(b);
      float angleIncrement = RandomRange(minAngle, maxAngle, b);

      //Calculate base properties.
      int sectionCount = int(length / sectionSpacing);
      vec3 up = vec3(0, 1, 0);
      vec3 sideDirection = cross(direction, up);
      vec3 sideBase = sideDirection * width;
      vec3 basePosition = gl_in[0].gl_Position.xyz + direction * bladeRadius;

      //Update position to terrain height.
      vec2 textureCoord = basePosition.xz / terrain.TotalSize + vec2(0.5);
      float height = texture(heightMapTexture, textureCoord).x * terrain.MaxHeight;
      basePosition.y = height;

      vec3 sectionPosition = basePosition;
      vec3 sectionNormal = direction;
      float taper = 1;
      vec3 side = sideBase;
      float angle = angleIncrement;

      for (int i = 0; i < sectionCount; i++)
      {
         //Output vertex
         OutputNormal(sectionNormal);
         OutputVertex(sectionPosition + side);
         OutputVertex(sectionPosition - side);

         //Calculate new section position and normals.
         angle += angleIncrement;
         taper = taper * taperFactor;
         side = sideBase * taper;
         vec3 newSectionPosition = sectionPosition + mix(up, direction, angle) * sectionSpacing;
         sectionNormal = normalize(cross(newSectionPosition - sectionPosition, sideDirection));
         sectionPosition = newSectionPosition;
      }

      //Output end vertex.
      OutputNormal(sectionNormal);
      OutputVertex(sectionPosition);

      EndPrimitive();
   }
}