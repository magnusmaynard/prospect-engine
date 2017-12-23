#version 450

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 ViewDirection;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (location = 2) uniform mat4 model;

void main()
{
   gl_Position = vec4(1);
}
