#pragma once
#include "Particle.hpp"

class Dust :public Emitter
{
	class Dustflake :public Snowflake
	{
		int x, y;

	public:
		Dustflake(int duration, int x, int y) :Snowflake(duration), x(x), y(y) {}
		void update()override
		{

		}
		void draw()const override
		{

		}
	};

public:
	Dust(int spawnrate) :Emitter(spawnrate) {}

	std::unique_ptr<Snowflake> generate()override
	{
		return (RI(0, 20)) ? nullptr : std::unique_ptr<Snowflake>(new Dustflake(RI(60, 180), RI(0, common::width), RI(0, common::height)));
	}
};

