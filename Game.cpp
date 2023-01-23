#include "Game.hpp"
#include "common.hpp"
#include "convert_string.hpp"
#include "common_functions.hpp"
#include "Input.hpp"

void Game::preset()
{
	//Particle::set<Dust>(20);
	Draw::font = LoadFontDataToHandle("data/font/NotoSansJPLight.dft");
}

Game::Message Game::update()
{
	if(Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	//Particle::draw();
}

