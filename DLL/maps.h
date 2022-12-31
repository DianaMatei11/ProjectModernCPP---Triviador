#pragma once
#include<utility>
#include<algorithm>
#ifdef MAPS_EXPORT
#define MAPS_API _declspec(dllexport)
#else
#define MAPS_API _declspec(dllimport)
#endif // Main_EXPORT

class MAPS_API maps
{
};

