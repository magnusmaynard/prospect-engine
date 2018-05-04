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
   int MaxLevels;
   float BladeCountMultiplier;
} vs_out;

void main()
{
   gl_Position = vec4(point, 1);

   float depth = (camera.PerspectiveProjection * camera.View * gl_Position).z;

   float maxDepth = 100;
   int maxLevels = 3;
   float lodDepth = maxDepth / maxLevels;

   int lod = int(depth / lodDepth);

   vs_out.Lod = lod;
   vs_out.MaxLevels = maxLevels;
   vs_out.BladeCountMultiplier = 1 - lod / maxLevels;
}