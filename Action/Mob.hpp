#pragma once
#include "Object.hpp"
#include <functional>
#include <queue>

class Mob : public Object
{
	bool interrupt;
	std::queue<std::pair<int, std::function<bool(Mob&)>>> command;

public:
	Mob(float x, float y) :Object(x, y), interrupt(true) {}


	void Dash(char d);
	void Jump();
	void FlyDash(char d);
	void FallKnock();

	void update();
};

