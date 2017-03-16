#version 450

//Renders skydome from space.
//http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html

uniform float time;
uniform vec2 resolution;

const vec3 EYE_POSITION = vec3(0, 0, -2);//vec3(0, 0, -1 + sin(time) * 1.0);
const vec3 EARTH_POSITION = vec3(0, 0, 0);
//const vec3 SUN_DIRECTION = vec3(0, 0, -1);
const vec3 SUN_DIRECTION = vec3(cos(time), 0, sin(time));

const float K_M = 0.0025f; //Rayleigh scatter constant
const float K_R = 0.0015f; //Mie scatter constant
const float E_SUN = 10.0f; //Sun intensity
const vec3 INVERSE_WAVELENGTH = vec3(
  1.0f / pow(0.650f, 4),
  1.0f / pow(0.570f, 4),
  1.0f / pow(0.475f, 4));


const int IN_SCATTER_SAMPLES = 10;
const int OUT_SCATTER_SAMPLES = 10;

const float MAX_HEIGHT = 1.0;

const float K_RAYLEIGH = 0.166;
const float K_MIE = 0.0025;

const float PI = 3.14159265359;

out vec4 color;

//TODO: How does this handle perspectives?
vec3 rayDirection(const vec2 res, const vec2 coord)
{
   vec2 uv = -1.0 + (2.0 * (coord / res));
   vec2 uvScaled = uv * vec2(res.x / res.y, 1.0);

   return normalize(vec3(uvScaled, 1.0));
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
vec2 rayIntersectsSphere(const vec3 ray)
{
   vec2 intersections = vec2(0, 0);//Mag along ray

   vec3 D = ray; //Normalized ray direction. x = close, y = far.
   float R = earthRadius;
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
   
   intersections.x = Tca - Thc; //Closest intersection;
   intersections.y = Tca + Thc; //Furthest intersection;

   return intersections;
}

float phase(float theta, float g) //How much light is scattered towards the camera.
{
   float cosTheta = cos(theta);
   float g2 = g * g;

   float lhs = (3 * (1 - g2)) / (2 * (2 + g2));
   float rhs = (1 + (cosTheta * cosTheta)) / pow(1 + g2 - 2 * g * cosTheta, 3.0 / 2.0);

   return lhs * rhs;
}

float optic(vec3 ray, vec2 intersects)
{
   vec3 startPoint = ray * intersects.x;
   vec3 endPoint = ray * intersects.y;
   vec3 section = (endPoint - startPoint) / OUT_SCATTER_SAMPLES;

   float sum = 0.0;
   for(int i = 0; i < OUT_SCATTER_SAMPLES; i++)
   {
      vec3 samplePoint = section * i;

      float height = length(earthPosition - samplePoint);
      float e = exp(-height / MAX_HEIGHT);
      sum += e;
   }

   sum /= OUT_SCATTER_SAMPLES;
   sum *= length(endPoint - startPoint);
   return sum;
}

vec3 outScattering(vec3 ray, vec2 intersects)
{
   vec3 startPoint = ray * intersects.x;
   vec3 endPoint = ray * intersects.y;

   float raySunAngle = acos(dot(ray, SUN_DIRECTION)); //Already normalized.

   float optic = optic(ray, intersects);

   return vec3(phase(raySunAngle, C_R.x) * optic, phase(raySunAngle, C_R.y) * optic, phase(raySunAngle, C_R.z) * optic);
}

vec3 InScattering()
{
   //loop
   
return I * 

}

void main()
{
   vec3 ray = rayDirection(resolution, gl_FragCoord.xy);

   vec2 intersects = rayIntersectsSphere(ray);

   color = vec4(outScattering(ray, intersects), 1);

   //if(intersections.x > 0 && intersections.y > 0) //2 intersections
   //{
   //   color = vec4(1.0, 1.0, 0.0, 1.0);
   //}
   //else if(intersections.x > 0) //1 intersection
   //{
   //   color = vec4(1.0, 0.0, 0.0, 1.0);
   //}
   //else //no intersections.
   //{
   //   color = vec4(intersections.x, intersections.y, 0.0, 1.0);
   //}
}