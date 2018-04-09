#version 450

layout (std140, binding = 0) uniform CameraUniforms
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

void main()
{
   gl_Position = camera.PerspectiveProjection * camera.View * vec4(point, 1);
}
