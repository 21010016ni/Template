#pragma once
#include <random>

#define USE_RESOURCE
#define USE_CONSOLE

namespace common
{
	extern int width;
	extern int height;
	extern int colorbit;
	extern int fps;
	extern bool windowmode;

	extern std::mt19937 engine;

	constexpr float pi = 3.14159265359f;
	constexpr float pi2 = 6.28318530718f;
}

