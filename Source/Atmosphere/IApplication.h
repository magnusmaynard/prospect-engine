#pragma once

class IApplication
{
public:
   virtual ~IApplication(){}

   virtual void Startup() = 0;
   virtual void Shutdown() = 0;
   virtual void Render(const double time) = 0;
   virtual void OnKeyPressed(int key, int action, int mods) = 0;
};