#version 450

//Renders skydome from space.
//http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html

//Global Uniforms
layout (std140) uniform CameraUniforms
{
   mat4 Projection;
   mat4 View;
   vec4 Position;
   vec2 ScreenSize;
} camera;

layout (std140) uniform DirectionalLightUniforms
{
   vec4 Direction;
} light;

//Local Uniforms
layout (std140) uniform AtmosphereUniforms //TODO: Dont use binding.
{
   vec4 EyePosition;
} atmosphere;

//Output
out vec4 color;

//Configuration
const vec3 EARTH_POSITION = vec3(0, 0, 0);
const float EARTH_OUTTER_RADIUS = 2000.0;
const float EARTH_INNER_RADIUS = 1500.0;
const float MAX_HEIGHT = EARTH_OUTTER_RADIUS - EARTH_INNER_RADIUS; //Thickness of atmosphere.
const float SCALE_HEIGHT = 0.25; //Height of average density of atmosphere.
const float SCALE = 1.0 / (EARTH_OUTTER_RADIUS - EARTH_INNER_RADIUS);

const int IN_SCATTER_SAMPLES = 10;
const float IN_SCATTER_SAMPLES_F = 10.0f;
const int OUT_SCATTER_SAMPLES = 10;
const float OUT_SCATTER_SAMPLES_F =10.0f;

//Scattering Constants.
const float G_MIE = -0.85;
const float G_MIE2 = G_MIE * G_MIE;
const float I_SUN = 20.0; //Sun intensity.
float K_MIE = 0.0025; //Scatter constants.
float K_RAYLEIGH = 0.015f;//Higher == redder.
const vec3 INVERSE_WAVELENGTH = vec3(
  1.0f / pow(0.650f, 4),
  1.0f / pow(0.570f, 4),
  1.0f / pow(0.475f, 4));

//Maths Constants
const float PI = 3.14159265359;

//http://antongerdelan.net/opengl/raycasting.html
vec3 RayFromCamera(const vec2 point)
{
   vec2 position = vec2((2.0 * point) / camera.ScreenSize - 1.0); //Normalised
   vec4 rayClip = vec4(position, -1.0, 1.0);
   vec4 rayEye = vec4((inverse(camera.Projection) * rayClip).xy, -1.0, 0.0);
   vec3 rayWorld = (inverse(camera.View) * rayEye).xyz;

   return normalize(rayWorld);
}

//Calculates near and far distances along a ray that intersects with a sphere.
//Returns minimum of 0. When inside the sphere, near returns 0.
//From: https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
// d = -(l . (o - c)) +- sqrt(((l . (o - c))^2 - ||o - c||^2 + r^2)
vec2 RaySphereIntersection(
   const vec3 o, //Ray origin.
   const vec3 l, //Ray direction.
   const vec3 c, //Sphere position.
   const float r) //Sphere radius.
{
   vec2 nearFar = vec2(0, 0); //x = near, y = far.

   float x = (dot(l, (o - c)) * dot(l, (o - c))) - dot(o - c, o - c) + (r * r);

   if(x < 0)//No intersection.
   {
      return nearFar;
   }
   else //Intersections.
   {
      float a = -dot(l, o - c);
      float b = sqrt(x);

      nearFar.x = max(0, a - b);
      nearFar.y = max(0, a + b);
      return nearFar;
   }
}

//TODO: Light does not seem to go around earth, maybe intersection are clipping the inner sphere.
bool RayEarthIntersections(const vec3 position, const vec3 ray, out vec2 nearFar) // out vec3 far
{
   vec2 outterNearFar = RaySphereIntersection(position, ray, EARTH_POSITION, EARTH_OUTTER_RADIUS);
   vec2 innerNearFar = RaySphereIntersection(position, ray, EARTH_POSITION, EARTH_INNER_RADIUS);

   if(outterNearFar.y == 0)//No intersections.
   {
      return false;
   }

   nearFar.x = outterNearFar.x;

   if(innerNearFar.x == 0) //Just outter intersect.
   {
      nearFar.y = outterNearFar.y;
   }
   else //Inner intersect.
   {
      nearFar.y = innerNearFar.x;
   }
   return true;
}

//Phase function for Rayleigh Scattering. g = 0
float RayleighPhase(float cos2)
{
   return 0.75 * (1.0 + cos2);
}

//Phase function for Mie Scattering.
float MiePhase(float g1, float g2, float cos1, float cos2)
{
   float top = 1.5 * (1.0 - g2) * (1.0 + cos2);
   float bot = (1.0 + g2 - 2.0 * g1 * cos1); //Intermediate step to cancel out 2 of the square roots.
   bot = (2.0 + g2) * bot * sqrt(bot);

   return top / bot;
}

//Get density of a given sample point.
float Density(vec3 samplePoint)
{
   float sampleHeight = (length(EARTH_POSITION - samplePoint) - EARTH_INNER_RADIUS) / MAX_HEIGHT;
   return exp(-sampleHeight / SCALE_HEIGHT);
}

//Average atmospheric density between two intersection points.
float OpticDepth(vec3 near, vec3 far) //Start and end intersections.
{
   float totalDensity = 0.0;
   vec3 increment = (far - near) / OUT_SCATTER_SAMPLES_F;
   vec3 samplePoint = near + (increment * 0.5);

   for(int i = 0; i < OUT_SCATTER_SAMPLES; i++)
   {
      totalDensity += Density(samplePoint);
      samplePoint += increment;
   }
   return totalDensity * length(increment) * SCALE;
}

float OutScattering(vec3 near, vec3 far)
{
   return 4 * PI * OpticDepth(near, far);
}

vec3 InScattering(vec3 ray, vec3 near, vec3 far)
{
   vec3 totalScattering = vec3(0, 0, 0);
   vec3 increment = (far - near) / IN_SCATTER_SAMPLES_F;

   vec3 samplePoint = near + (increment * 0.5);

   for(int i = 0; i < IN_SCATTER_SAMPLES; i++)
   {
      //Out scattering to sun.
      vec3 sunRay = -light.Direction.xyz;
      vec2 sunNearFar = RaySphereIntersection(samplePoint, sunRay, EARTH_POSITION, EARTH_OUTTER_RADIUS);

      vec3 farPoint = samplePoint + (sunRay * sunNearFar.y);
      float sunOutScattering = OutScattering(samplePoint, farPoint);

      //Out scattering to camera.
      float cameraOutScattering = OutScattering(near, samplePoint);
      vec3 outScattering = exp((-(sunOutScattering + cameraOutScattering)) * (INVERSE_WAVELENGTH * K_RAYLEIGH + K_MIE));

      totalScattering += Density(samplePoint) * outScattering;

      samplePoint += increment;
   }

   totalScattering = totalScattering * length(increment) * SCALE;

   float c1 = dot(ray, light.Direction.xyz);
   float c2 = c1 * c1;

   vec3 rayleigh = I_SUN * K_RAYLEIGH * INVERSE_WAVELENGTH * RayleighPhase(c2) * totalScattering;
   vec3 mie = I_SUN * K_MIE * MiePhase(G_MIE, G_MIE2, c1, c2) * totalScattering;
   return rayleigh + mie;
}

void main()
{
   vec3 eyePosition = atmosphere.EyePosition.xyz;//vec3(0, 1500.1, 0);// atmosphere.EyePosition.xyz;
   vec3 ray = RayFromCamera(gl_FragCoord.xy);

   vec2 nearFar = vec2(0, 0);
   bool hasIntersected = RayEarthIntersections(eyePosition, ray, nearFar);

   color = vec4(0, 0, 0, 0);

   if(hasIntersected)
   {
      vec3 near = eyePosition + (ray * nearFar.x);
      vec3 far = eyePosition + (ray * nearFar.y);

      vec3 I = InScattering(ray, near, far);

      color = vec4(I, 1.0);
   }
}