#version 450

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

layout (location = 0) in vec3 point;

out VS_OUT
{
   int Lod;
   int LodMax;
} vs_out;

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
   return mix(min, max, GoldNoise(gl_Position.xz, 45 + seed));
}

void main()
{
   gl_Position = vec4(point, 1);

   float dither = RandomRange(-10, 10, 7);
   float depth = (camera.PerspectiveProjection * camera.View * gl_Position).z + dither;

   float maxDepth = 80;
   int lodMax = 3;
   float depthPerLod = maxDepth / lodMax;

   //3 = most detailed, 0 = least detailed.
   int lod = int(depth / depthPerLod);

   vs_out.Lod = lod;
   vs_out.LodMax = lodMax;
}