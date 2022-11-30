#include "Mob.hpp"
#include "Config.hpp"

void Mob::Dash(char d)
{
	if (interrupt)
	{
		while (!command.empty())
			command.pop();
		if (d > 0)
		{
			command.emplace(1, [](Mob& u) {u.vec.x = 8.0f; return false; });
		}
		else if (d < 0)
		{
			command.emplace(1, [](Mob& u) {u.vec.x = -8.0f; return false; });
		}
	}
}

void Mob::Jump()
{
	if (interrupt)
	{
		while (!command.empty())
			command.pop();
		command.emplace(1, [](Mob& u) {if (u.vec.y > 0)u.vec.y = 0; u.vec.y -= 15.0f; return true; });
		command.emplace(2, [](Mob&) {return true; });
		command.emplace(17, [](Mob&) {return false; });
	}
}

void Mob::FlyDash(char d)
{
	if (interrupt)
	{
		while (!command.empty())
			command.pop();
		command.emplace(1, [](Mob& u) {u.vec.y = -15.0f; return true; });
		command.emplace(4, [](Mob&) {return true; });
		command.emplace(5, [](Mob&) {return false; });
		command.emplace(0, [](Mob& u) {u.vec.y = 0; return false; });
		if (d > 0)
			command.emplace(1, [](Mob& u) {u.vec.x = 20.0f; return false; });
		else if (d < 0)
			command.emplace(1, [](Mob& u) {u.vec.x = -20.0f; return false; });
		command.emplace(10, [](Mob& u) {u.vec.y = 0.0f; return true; });
		command.emplace(10, [](Mob&) {return false; });
	}
}

void Mob::FallKnock()
{
	if (interrupt)
	{
		while (!command.empty())
			command.pop();
		command.emplace(5, [](Mob& u) {u.vec.y = 0.0f; return false; });
		command.emplace(5, [](Mob& u) {u.vec.y += 5.0f; return true; });
		command.emplace(20, [](Mob& u) {return false; });
	}
}

void Mob::update()
{
	vec += gravity;
	vec.x *= 0.9;
	if (command.empty())
	{
		interrupt = true;
	}
	while (!command.empty())
	{
		interrupt = command.front().second(*this);
		if (command.front().first <= 0)
		{
			command.pop();
			continue;
		}
		else if (--command.front().first <= 0)
			command.pop();
		break;
	}
	move();
	if (pos.y > common::height)
	{
		pos.y = common::height;
		vec.y = 0;
	}
}

