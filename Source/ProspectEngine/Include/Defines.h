#pragma once

#ifdef COMPILING_DLL 
/*Enabled as "export" while compiling the dll project*/
#define EXPORT_DLL __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define EXPORT_DLL __declspec(dllimport)  
#endif