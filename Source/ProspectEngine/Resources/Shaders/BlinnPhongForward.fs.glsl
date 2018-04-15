#version 450

struct Material
{
   vec4 Diffuse;
   vec4 Ambient;
   vec4 SpecularAndPower;
};

layout (std140) uniform MaterialLibraryUniforms
{
   Material Materials[10];
} materialLibrary;

out vec4 color;

void main()
{
   vec3 diffuse  = vec3(gl_FragCoord.x /2000.f, gl_FragCoord.y / 1000.f, 0);
   float alpha = 0.4;

   color = vec4(diffuse.r * alpha, diffuse.g * alpha, diffuse.b * alpha, alpha);
   // color = vec4(diffuse.r, diffuse.g, diffuse.b, alpha);
}