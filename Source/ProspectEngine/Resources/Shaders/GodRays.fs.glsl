#version 450

layout(binding = 0) uniform sampler2D displayTexture;
layout(binding = 1) uniform sampler2D albedoTexture;
layout(binding = 2) uniform sampler2D depthTexture;

layout(std140) uniform CameraUniforms
{
   mat4 PerspectiveProjection;
   mat4 InversePerspectiveProjection;
   mat4 OrthographicProjection;
   mat4 View;
   mat4 InverseView;
   vec4 Position;
   vec2 ScreenSize;
}
camera;

layout(std140) uniform GodRaysUniforms
{
   vec4 SunPosition;
}
godRays;

in VS_OUT
{
   vec2 textureCoords;
}
fs_in;

out vec4 color;

void main()
{
   // Sun Shafts
   // http://fabiensanglard.net/lightScattering/
   //    float exposure = 0.0034f;
   //    float decay = 1.0;
   //    float density = 0.84f;
   //    float weight = 5.65f;
   //    const int NUM_SAMPLES = 100;

    vec3 viewDirection = -vec3(camera.View[0][2], camera.View[1][2], camera.View[2][2]);
    vec3 sunDirection = -godRays.SunPosition.xyz;
    if(dot(viewDirection, sunDirection) > 0)
    {
        //Sun is pointing in the wrong direction.
        return;
    }

   float exposure = 0.0014f;
   float decay = 0.995;
   float density = 0.84f;
   float weight = 1.65f;
   const int NUM_SAMPLES = 100;

   vec4 clipSunPosition =
       camera.PerspectiveProjection * camera.View * vec4(godRays.SunPosition.xyz, 1);
   vec3 ndcSunPosition = clipSunPosition.xyz / clipSunPosition.w;
   vec2 screenSunPosition = ((ndcSunPosition.xy + 1.0) / 2.0);

   vec2 deltaTextCoord = vec2(fs_in.textureCoords.xy - screenSunPosition);
   vec2 textCoo = fs_in.textureCoords.xy;
   deltaTextCoord *= 1.0 / float(NUM_SAMPLES) * density;
   float illuminationDecay = 1.0;

   for (int i = 0; i < NUM_SAMPLES; i++)
   {
      textCoo -= deltaTextCoord;

      float depth = texture2D(depthTexture, textCoo).x;

      vec4 samplee;
      if (depth == 1)
      {
         // sky
         samplee = texture2D(displayTexture, textCoo);
      }
      else
      {
         // obstructions
         samplee = vec4(0);
      }

      samplee *= illuminationDecay * weight;

      color += samplee;

      illuminationDecay *= decay;
   }
   color *= exposure;
}