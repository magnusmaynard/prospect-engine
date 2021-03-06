﻿#version 450

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

layout (std140) uniform SunUniforms
{
   mat4 Model;
   uvec4 MaterialID;
} sun;

layout (location = 0) in vec3 point;

out VS_OUT
{
   vec3 Normal;
} vs_out;

void main()
{
   //Remove translation from view.
   mat4 viewNoTranslation = camera.View;
   viewNoTranslation[3][0] = 0;
   viewNoTranslation[3][1] = 0;
   viewNoTranslation[3][2] = 0;
   viewNoTranslation[0][3] = 0;
   viewNoTranslation[1][3] = 0;
   viewNoTranslation[2][3] = 0;
   viewNoTranslation[3][3] = 1;

   //Remove all rotational components from the view model,
   //to make object always face the same direction.
   mat4 modelView2D = viewNoTranslation * sun.Model;
   modelView2D[0][0] = 1;
   modelView2D[0][1] = 0;
   modelView2D[0][2] = 0;
   modelView2D[1][0] = 0;
   modelView2D[1][1] = 1;
   modelView2D[1][2] = 0;
   modelView2D[2][0] = 0;
   modelView2D[2][1] = 0;
   modelView2D[2][2] = 1;
   
   vs_out.Normal = vec3(0, 0, 1);//Normal doesn't matter as it is unlit.

   gl_Position = camera.PerspectiveProjection * modelView2D * vec4(point, 1.0);
}
