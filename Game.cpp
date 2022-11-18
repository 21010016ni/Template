#include "Game.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "Effect.h"

void Game::preset()
{
}

Game::Message Game::update()
{
	Particle::update();
	if (Keyboard::push(VK_SPACE))
	{
		Particle::emit<Effect>(common::width / 2, common::height / 2);
	}
	if (Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}
	return Message::none;
}

void Game::draw()
{
	Particle::draw();
}
