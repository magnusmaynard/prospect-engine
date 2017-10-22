#version 450

layout (std140, binding = 0) uniform CameraUniforms
{
   mat4 Projection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

layout (location = 0) in vec3 point;

void main()
{
  // gl_Position = projection * view * vec4(point + vec3(time, 0, 0), 1.0);
   gl_Position = camera.Projection * camera.View * model * vec4(point, 1.0);
}
