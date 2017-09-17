#pragma once
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <noise/noise.h>

#include <iostream>

typedef unsigned char byte;

int main()
{
   int size = 400;
   float sizef = static_cast<float>(size);
   std::string fileName = "terrain1.bmp";

   noise::module::Perlin perlin;
   //perlin.SetOctaveCount(10);
   //perlin.SetFrequency(3.0);
   perlin.SetSeed(1);

   perlin.SetOctaveCount(6);
   perlin.SetFrequency(2.5);
   perlin.SetPersistence(0.6);

   int currentIndex = 0;
   std::vector<byte> data;
   data.resize(size * size);

   for (int y = 0; y < size; y++)
   {
      for (int x = 0; x < size; x++)
      {
         float elevation = static_cast<float>(perlin.GetValue(
            (float)x / sizef,
            (float)y / sizef,
            0.0));


         if(elevation > 1 || elevation < -1)
         {
            std::cout << elevation << std::endl;
         }

            float temp = (1 + elevation) / 2.f;

         data[currentIndex] = byte(temp * 255.0);
         currentIndex++;
      }
   }

   auto success = stbi_write_bmp(fileName.c_str(), size, size, 1, &data[0]);

}
