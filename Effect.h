#pragma once
#include <functional>
#include "Particle.hpp"
#include "Draw.hpp"
#include "DxLib.h"

struct Shape
{
	unsigned char mode;
	unsigned int color;
	std::function<Point<float>(int)> p0;
	std::function<unsigned char(int)> value;

	Shape(unsigned char mode, unsigned int color, std::function<Point<float>(int)> p0, std::function<unsigned char(int)> value)
		:mode(mode), value(value), color(color), p0(p0)
	{}

	virtual void draw(const Draw& draw, int t)const = 0;
};

struct Circle :public Shape
{
	float r;
	int num;
	bool fill;
	float thick;

	Circle(unsigned char mode, unsigned int color, float r, int num, bool fill, float thick, std::function<Point<float>(int)> p, std::function<unsigned char(int)> value)
		:Shape(mode, color, p, value), r(r), num(num), fill(fill), thick(thick)
	{}

	void draw(const Draw& draw, int t)const override
	{
		draw.blend(mode, value(t));
		draw.circleAA(p0(t), r, num, color, fill, thick);
	}
};

class Effect :public Snowflake
{
	Draw d;
	int t;
	std::vector<std::unique_ptr<Shape>> shape;

public:
	Effect(int x, int y);

	void update()override
	{
		++t;
	}
	void draw()const override
	{
		for (const auto& i : shape)
			i->draw(d, t);
	}
};

