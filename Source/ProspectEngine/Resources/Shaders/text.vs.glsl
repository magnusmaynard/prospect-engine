#version 450

layout (std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   vec4 ViewDirection;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform TextUniforms
{
   vec4 Model;
} text;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoords;

out vec2 textureCoord;

void main()
{
   textureCoord = textureCoords;

   gl_Position = camera.OrthographicProjection * text.Model * vec4(position, 0, 1);
}
