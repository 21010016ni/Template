#pragma once
#include "Point.hpp"
#include "Draw.hpp"

class Object
{
public:
	static Draw d;
	static Point<float> gravity;

	Point<float> pos;
	Point<float> vec;

	Object(float x, float y) :pos(y, x), vec(0.0f, 0.0f) {}

	void move() { pos += vec; }

	virtual void draw()const;
};

