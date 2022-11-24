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
	static int effect = -1;
	if (Mouse::click(MOUSE_INPUT_1))
	{
		if(effect == -1)
		{
			Effect::TestWrite();
			effect = Effect::load("data.bin");
		}
		Effect::emit(Mouse::x(), Mouse::y(), effect);
	}
	if (Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}
	Particle::update();
	return Message::none;
}

void Game::draw()
{
	Particle::draw();
}
