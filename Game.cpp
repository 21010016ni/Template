#include "Game.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "Effect.hpp"
#include "ParticleDust.hpp"

void Game::preset()
{
	Particle::set<Dust>(20);
}

Game::Message Game::update()
{
	Particle::update();
	if (Mouse::click(MOUSE_INPUT_1))
	{
		Particle::emit<Effect>(Mouse::x(), Mouse::y());
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
