#version 450

//Renders skydome from space.
//http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html

//Input
uniform float time;
uniform vec2 resolution;
uniform vec3 sunDirection;

//Output
out vec4 color;

//Configuration
//const vec3 EYE_POSITION = vec3(0, 1.01, -1.0 + sin(time) * 1.2); ////vec3(0, 0, -2);
const vec3 EYE_POSITION =vec3(0, 0, -1.8);//vec3(0, 1.001, -1.2);//vec3(0, 1.01, -1.0 + sin(time * 0.1) * 1.2); ////vec3(0, 0, -2);
//const vec3 EYE_POSITION = vec3(0, 1.001, 0);
const vec3 EARTH_POSITION = vec3(0, 0, 0);
const float EARTH_OUTTER_RADIUS = 1.05;
const float EARTH_INNER_RADIUS = 1.0;
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
const float I_SUN = 14.0; //Sun intensity.
float K_MIE = 0.0025; //Scatter constants.
float K_RAYLEIGH = 0.010f;//Higher == redder.
const vec3 INVERSE_WAVELENGTH = vec3(
  1.0f / pow(0.650f, 4),
  1.0f / pow(0.570f, 4),
  1.0f / pow(0.475f, 4));

//Maths Constants
const float PI = 3.14159265359;

//TODO: How does this handle perspectives?
vec3 RayFromCamera(const vec2 res, const vec2 coord)
{
   vec2 uv = -1.0 + (2.0 * (coord / res));
   vec2 uvScaled = uv * vec2(res.x / res.y, 1.0);

   return normalize(vec3(uvScaled, 1.0));
}

//TODO: Sort out input parameters.
//Calculates near and far distances along a ray that intersects with a sphere.
//Returns minimum of 0. When inside the sphere, near returns 0.
//From: https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
// d = -(l . (o - c)) +- sqrt(((l . (o - c))^2 - ||o - c||^2 + r^2)
vec2 RayIntersections(
   const vec3 rayOrigin,
   const vec3 rayDirection,
   const float sphereRadius)
{
   vec2 nearFar = vec2(0,0);

   vec3 o = rayOrigin;
   vec3 l = rayDirection;
   vec3 c = EARTH_POSITION;
   float r = sphereRadius;

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
bool CalculateRayIntersections(const vec3 position, const vec3 ray, out vec2 nearFar) // out vec3 far
{
   vec2 outterNearFar = RayIntersections(position, ray, EARTH_OUTTER_RADIUS);
   vec2 innerNearFar = RayIntersections(position, ray, EARTH_INNER_RADIUS);

   if(outterNearFar.y == 0)//No intersections.
   {
     // color.x = 1.0;
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
   vec3 totalScattering;
   vec3 increment = (far - near) / IN_SCATTER_SAMPLES_F;

   vec3 samplePoint = near + (increment * 0.5);

   for(int i = 0; i < IN_SCATTER_SAMPLES; i++)
   {
      //Out scattering to sun;
      vec3 sunRay = -sunDirection;
      vec2 sunNearFar = RayIntersections(samplePoint, sunRay, EARTH_OUTTER_RADIUS);

      vec3 farPoint = samplePoint + (sunRay * sunNearFar.y);
      float sunOutScattering = OutScattering(samplePoint, farPoint);

      //Out scattering to camera
      float cameraOutScattering = OutScattering(near, samplePoint);

      vec3 outScattering = exp((-(sunOutScattering + cameraOutScattering)) * (INVERSE_WAVELENGTH * K_RAYLEIGH + K_MIE));

      totalScattering += Density(samplePoint) * outScattering;

      samplePoint += increment;
   }
   totalScattering = totalScattering * length(increment) * SCALE;

   float c1 = dot(ray, sunDirection);
   float c2 = c1 * c1;

   vec3 rayleigh = I_SUN * K_RAYLEIGH * INVERSE_WAVELENGTH * RayleighPhase(c2) * totalScattering;
   vec3 mie = I_SUN * K_MIE * MiePhase(G_MIE, G_MIE2, c1, c2) * totalScattering;
   return rayleigh + mie;
}

void main()
{
   vec3 ray = RayFromCamera(resolution, gl_FragCoord.xy);

   color = vec4(0,0,0,1);
   vec2 nearFar = vec2(0,0);
   bool hasIntersected = CalculateRayIntersections(EYE_POSITION, ray, nearFar);

   if(hasIntersected)
   {
      vec3 near = EYE_POSITION + (ray * nearFar.x);
      vec3 far = EYE_POSITION + (ray * nearFar.y);

      vec3 I = InScattering(ray, near, far);

      color = vec4(I, 1.0);
      //float exposure = 2.0;
      //color =   vec4(1.0 - exp(-exposure * I.x), 1.0 - exp(-exposure * I.y), 1.0 - exp(-exposure * I.z), 1.0);
   }
}