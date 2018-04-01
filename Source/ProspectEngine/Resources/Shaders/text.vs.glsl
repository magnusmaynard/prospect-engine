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

layout (location = 10) uniform mat4 model;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoords;

out vec2 textureCoord;

void main()
{
   textureCoord = textureCoords;

   vec2 screenOffset = camera.ScreenSize * 0.5;
   gl_Position = camera.OrthographicProjection * model * vec4(position - screenOffset, 0, 1);
}
