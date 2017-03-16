#version 450

//Renders skydome from space.
//http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html

//Input
uniform float time;
uniform vec2 resolution;

//Output
out vec4 color;

//Configuration
const vec3 EYE_POSITION = vec3(0, 1.01, -1.0 + sin(time) * 1.2);//vec3(0, 0, -2);//
//const vec3 SUN_DIRECTION = vec3(0, 0, -1);
const vec3 SUN_DIRECTION = vec3(cos(time), 0, sin(time));
const vec3 EARTH_POSITION = vec3(0, 0, 0);
const float EARTH_OUTTER_RADIUS = 1.25;
const float EARTH_INNER_RADIUS = 1.0;
const float MAX_HEIGHT = EARTH_OUTTER_RADIUS - EARTH_INNER_RADIUS; //Thickness of atmosphere.
const float SCALE_HEIGHT = 0.25; //Height of average density of atmosphere.

const int IN_SCATTER_SAMPLES = 10;
const int OUT_SCATTER_SAMPLES = 10;
const float OUT_SCATTER_SAMPLES_F =10.0f;

//Scattering Constants.
const float K_MIE = 0.0025f; //Rayleigh scatter constant
const float K_RAYLEIGH = 0.0015f; //Mie scatter constant
const float E_SUN = 10.0f; //Sun intensity
const vec3 INVERSE_WAVELENGTH = vec3( //TODO: Do I want to Inverse?
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

//Edited: Now always return minimum of 0.
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
vec2 RayIntersections(const vec3 ray, const float radius)
{
   vec2 intersections = vec2(0, 0);//Mag along ray

   vec3 D = ray; //Normalized ray direction. x = close, y = far.
   float R = radius;
   vec3 C = EARTH_POSITION;
   vec3 O = EYE_POSITION;
   vec3 L = C - O;

   float Tca = dot(L, D);

   //if(Tca < 0) //Discard if behind O.
   //{
   //   return false;
   //}

   float d = sqrt(dot(L, L) - dot(Tca, Tca)); //TODO: remove sqrt

   if(d > R) //Greater than radius means they cannot intersect.
   {
      return intersections;
   }

   float Thc = sqrt((R * R) - (d * d));
   
   intersections.x = max(0, Tca - Thc); //Closest intersection;
   intersections.y = max(0, Tca + Thc); //Furthest intersection;

   return intersections;
}

bool CalculateRayIntersections(const vec3 ray, out vec2 nearFar) // out vec3 far
{
   vec2 outterNearFar = RayIntersections(ray, EARTH_OUTTER_RADIUS);
   vec2 innerNearFar = RayIntersections(ray, EARTH_INNER_RADIUS);

   //if(outterNearFar.y == 0)//No intersections.
   //{
   //   return false;
   //}
   //else if(outterNearFar.x == 0) //Inside atmosphere.
   //{
   //   near = 0.0;
      
   //   if(innerNearFar.x == 0)//Just outter intersect.
   //   {
   //      far = outterNearFar.y;
   //   }
   //   else  //Inner intersect.
   //   {
   //      far = innerNearFar.x;
   //   } 
   //}
   //else //Outside atmosphere
   //{
   //   near = outterNearFar.x;

   //   if(innerNearFar.x == 0) //Just outter intersect.
   //   {
   //      far = outterNearFar.y;
   //   }
   //   else //Inner intersect.
   //   {
   //      far = innerNearFar.x;
   //   }
   //}

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

//Phase function for Rayleigh Scattering.
//g = 0
float RayleighPhase(float cos2)
{
   return 0.75 * (1.0 + cos2);
}

//Phase function for Mie Scattering.
//g = -0.75 to -0.999
float MiePhase(float g1, float g2, float cos1, float cos2)
{
   float top = 1.5 * (1.0 - g2) * (1.0 + cos2);
   float bot = (1.0 + g2 - 2.0 * g1 * cos2); //Intermediate step to cancel out 2 of the square roots.
   bot = (2.0 + g2) * bot * sqrt(bot);

   return top / bot;
}

//Average atmospheric density between two intersection points.
float OpticDepth(vec3 a, vec3 b) //Start and end intersections.
{
   float totalOptic = 0.0;
   vec3 increment = (b - a) / OUT_SCATTER_SAMPLES_F;
   vec3 samplePoint = a + (increment * 0.5); //TODO: Do I need to sample in the middle, i.e offset by 0.5?
   float sampleHeight = 0.0;

   for(int i = 0; i < OUT_SCATTER_SAMPLES; i++)
   {
      samplePoint += increment;
      sampleHeight = (length(EARTH_POSITION - samplePoint) - EARTH_INNER_RADIUS) / MAX_HEIGHT;
      totalOptic += exp(-sampleHeight / SCALE_HEIGHT);
   }
   return (totalOptic / OUT_SCATTER_SAMPLES_F) * length(b - a); //TODO: Is this correct?

  // float total = 0.0;
  // for(int i = 0; i < OUT_SCATTER_SAMPLES; i++)
  // {

  //    total = length(samplePoint - EARTH_POSITION);// - EARTH_INNER_RADIUS;
  //    //totalOptic += exp(-sampleHeight / SCALE_HEIGHT);

  //    samplePoint += increment;
  // }
  // color.y = total *0.5;
  // //TODO: remove length()
  //return totalOptic;//temp
}

vec3 InScattering(vec3 ray, vec2 nearFar)
{
   //TODO: Implement scattering.


   vec3 near = EYE_POSITION + (ray * nearFar.x);
   vec3 far = EYE_POSITION + (ray * nearFar.y);

   float temp = OpticDepth(near, far);
   return vec3(temp, 0.0, 0.0);
   //return vec3(nearFar.y - nearFar.x, 0.0, 0.0);

}

void main()
{
   vec3 ray = RayFromCamera(resolution, gl_FragCoord.xy);

   vec2 nearFar;
   //vec3 far;
   bool hasIntersected = CalculateRayIntersections(ray, nearFar);

   if(hasIntersected)
   {
      vec3 I = InScattering(ray, nearFar);

      color = vec4(I, 1.0);
      //color.z = 1.0;
      //if(nearFar.x > 0 && nearFar.y > 0) //2 intersections
      //{
      //   color = vec4(0.0, 1.0, 0.0, 1.0);
      //}
      //else if(nearFar.x > 0) //1 intersection
      //{
      //   color = vec4(1.0, 0.0, 0.0, 1.0);
      //}
   }
}