﻿#version 450

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
   vec4 DiffuseColor;
} light;


void main()
{
   color = vec4(1);
}