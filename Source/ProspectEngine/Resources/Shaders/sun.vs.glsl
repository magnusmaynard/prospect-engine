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

layout (std140) uniform SunUniforms
{
   mat4 Model;
} sun;

layout (location = 0) in vec3 point;

void main()
{
   //Remove all rotational components from the view model,
   //to make object always face the same direction.
   mat4 modelView2D = camera.View * sun.Model;
   modelView2D[0][0] = 1;
   modelView2D[0][1] = 0;
   modelView2D[0][2] = 0;
   modelView2D[1][0] = 0;
   modelView2D[1][1] = 1;
   modelView2D[1][2] = 0;
   modelView2D[2][0] = 0;
   modelView2D[2][1] = 0;
   modelView2D[2][2] = 1;
   
   gl_Position = camera.PerspectiveProjection * modelView2D * vec4(point, 1.0);
}
