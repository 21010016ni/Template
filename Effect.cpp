#include "Effect.h"

Effect::Effect(int x, int y) :Snowflake(20), d(x, y, 8), t(0)
{
	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(3 - (float)t, 3 + sin(t * 0.2f) * 4); }, [](int t) {return 256 - t * 8; }));
	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(-2 - (float)t, -8 - sin(t * 0.2f) * 4); }, [](int t) {return 200 - t * 8; }));
	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(1 - (float)t, 6 + cos(t * 0.2f) * 4); }, [](int t) {return 224 - t * 8; }));
	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(4 - (float)t, -7 - cos(t * 0.2f) * 4); }, [](int t) {return 160 - t * 8; }));
	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(0 - (float)t, 1 + sin(t * 0.2f) * 4); }, [](int t) {return 190 - t * 8; }));
}

