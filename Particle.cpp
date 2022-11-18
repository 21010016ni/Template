#include "Particle.hpp"

void Particle::update()
{
	for (auto i = snowflake.begin(); i != snowflake.cend();)
	{
		(*i)->update();
		if (!(--(**i))())
		{
			i = snowflake.erase(i);
			continue;
		}
		++i;
	}
	for (const auto& i : emitter)
		if (i->spawn())
			snowflake.emplace_back(i->generate());
}

void Particle::draw()
{
	for (const auto& i : snowflake)
		i->draw();
}

