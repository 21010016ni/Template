#pragma once
#include <random>

namespace common
{
	extern int width;
	extern int height;
	extern int colorbit;
	extern int fps;

	extern std::mt19937 engine;

	constexpr float pi = 3.14159265359f;
	constexpr float pi2 = 6.28318530718f;
}
