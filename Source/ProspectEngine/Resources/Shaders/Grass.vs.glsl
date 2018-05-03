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
   vec3 position;
} vs_out;

void main()
{
   gl_Position = vec4(point, 1);
}