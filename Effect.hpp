#pragma once
#include <functional>
#include "Particle.hpp"
#include "Draw.hpp"
#include "DxLib.h"

struct Pixel
{
	unsigned char mode;
	unsigned int color;
	std::function<Point<float>(int)> p0;
	std::function<unsigned char(int)> value;

	Pixel(unsigned char mode, unsigned int color, std::function<Point<float>(int)> p0, std::function<unsigned char(int)> value)
		:mode(mode), value(value), color(color), p0(p0) {}

	virtual void draw(const Draw& draw, int t)const = 0;
};

struct Circle :public Pixel
{
	float r;
	int num;
	bool fill;
	float thick;

	Circle(unsigned char mode, unsigned int color, float r, int num, bool fill, float thick, std::function<Point<float>(int)> p, std::function<unsigned char(int)> value)
		:Pixel(mode, color, p, value), r(r), num(num), fill(fill), thick(thick) {}

	void draw(const Draw& draw, int t)const override
	{
		draw.blend(mode, value(t));
		draw.circleAA(p0(t), r, num, color, fill, thick);
	}
};

struct Line :public Pixel
{
	float thick;
	std::function<Point<float>(int)> p1;

	Line(unsigned char mode, unsigned int color, float thick, std::function<Point<float>(int)> p0, std::function<Point<float>(int)> p1, std::function<unsigned char(int)> value)
		:Pixel(mode, color, p0, value), thick(thick), p1(p1) {}

	void draw(const Draw& draw, int t)const override
	{
		draw.blend(mode, value(t));
		draw.lineAA(p0(t), p1(t), color, thick);
	}
};

struct Polygon :public Pixel
{
	void draw(const Draw& draw, int t)const override
	{
		
	}
};

class Effect :public Snowflake
{
	Draw d;
	int t;
	std::vector<std::unique_ptr<Pixel>> shape;

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

