#include "Game.hpp"
#include "common.hpp"
#include "convert_string.hpp"
#include "common_functions.hpp"
#include "Input.hpp"

#define _range(_value,_min,_max) __min(__max(_value,_min),_max)

int t;
int fonts[4];

//class Announce
//{
//	std::vector<std::u8string>
//};

Draw Game::display(0, 0, 0);

void Game::preset()
{
	//Particle::set<Dust>(20);
	//Draw::font = LoadFontDataToHandle("data/font/NotoSansJPLight.dft");
	fonts[0] = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	fonts[1] = CreateFontToHandle(NULL, 40, 2, DX_FONTTYPE_ANTIALIASING_4X4);
	t = 0;
}

Game::Message Game::update()
{
	if(Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}
	++t;

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	Draw::blend();
	if (t >= 60 && t < 120)
	{
		Draw::font = fonts[0];
		display.string(common::width / 2, common::height / 2, u8"ÅyåxçêÅz", 0xffffff, ref::center | ref::middle);
	}
	if (t >= 120 && t < 380)
	{
		Draw::font = fonts[1];
		display.string(common::width / 2, common::height / 2 - _range((t - 180) * 20, 0, 200), u8"Åyã≠êßé∑çsÅz", 0xffffff, ref::center | ref::middle);
	}
	if (t >= 220 && t < 380)
	{
		switch (__min((t - 220) / 30, 3))
		{
		case 3:
			display.string(common::width / 2, common::height / 2 + 200, u8"Åyâ§ÇÕàÍêlÅz", 0xffffff, ref::center | ref::middle);
			__fallthrough;
		case 2:
			display.string(common::width / 2, common::height / 2 + 100, u8"ÅyíNÇ‡ã~Ç¶Ç»Ç¢Åz", 0xffffff, ref::center | ref::middle);
			__fallthrough;
		case 1:
			display.string(common::width / 2, common::height / 2, u8"Åyè¡Ç¶Ç‰Ç≠íËÇﬂÅAñΩÇÃìîÅcÅcÅz", 0xffffff, ref::center | ref::middle);
			__fallthrough;
		case 0:
			display.string(common::width / 2, common::height / 2 - 100, u8"ÅyãtêbÇÃèàåYÅz", 0xffffff, ref::center | ref::middle);
		}
	}
	if (t >= 380)
	{
		if (t >= 485)
		{
			Draw::blend(blendmode::alpha, 32);
			Draw::font = fonts[1];
		}
		display.string(common::width / 2, common::height / 2 - _range((t - 380) * 20, 0, 100), u8"ÅyèüóòèåèÇ™í«â¡Ç≥ÇÍÇ‹ÇµÇΩÅz", 0xffffff, ref::center | ref::middle);
	}
	if (t >= 405)
	{
		switch (__min((t - 405) / 30, 1))
		{
		case 1:
			display.string(common::width / 2, common::height / 2 + 100, u8"Åyêßå¿éûä‘ÅF00.00Åz", 0xffffff, ref::center | ref::middle);
			__fallthrough;
		case 0:
			display.string(common::width / 2, common::height / 2, u8"ÅyèüóòèåèÅFåNéÂÇÃéEäQÅz", 0xffffff, ref::center | ref::middle);
		}
	}
	if (t >= 485)
	{
		Draw::blend();
		display.string(common::width / 2 - _range((t - 485) * 10, 0, 100), common::height / 2 - _range((t - 485) * 10, 0, 100), u8"Åyñ⁄ïWÅcÅcÅz", 0xffffff, ref::center | ref::middle);
	}
	if (t >= 545)
	{
		Draw::font = fonts[0];
		display.string(common::width / 2, common::height / 2, u8"ÅyåNéÂÅzÅyÉTÉgÉDÅzÅyLevel-24Åz", 0xffffff, ref::center | ref::middle);
	}

	//Particle::draw();
}

