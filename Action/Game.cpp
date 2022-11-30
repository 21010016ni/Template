#include "Game.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "Particle.hpp"

#include "Draw.hpp"
#include "convert_string.hpp"

#include "Mob.hpp"

Draw display(0, 0, 0);

void Game::preset()
{
	//Particle::set<Dust>(20);
}

Game::Message Game::update()
{
	static Mob player(200, 300);

	if (Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}
	else if (Keyboard::push(VK_SPACE))
	{
		player.Jump();
	}
	else if (Keyboard::press('D'))
	{
		player.Dash(1);
	}
	else if (Keyboard::press('A'))
	{
		player.Dash(-1);
	}
	else if (Keyboard::push('E'))
	{
		player.FlyDash(1);
	}
	else if (Keyboard::push('Q'))
	{
		player.FlyDash(-1);
	}
	else if (Keyboard::push('X'))
	{
		player.FallKnock();
	}

	player.update();
	Particle::update();
	player.draw();
	return Message::none;
}

void Game::draw()
{
	for (int i = 0; i < 256; ++i)
	{
		display.string(i / 16 * 32, i % 16 * 18, ext::vto<char8_t, int>(Keyboard::get(i)), 0xffffff);
	}

	Particle::draw();
}

