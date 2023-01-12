#include "Game.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "convert_string.hpp"

#include "Handle.hpp"

#include "Map.hpp"

Draw Game::display(0, 0, 0);
Map map;
char tool = 0;
char toolmode;
Point<int> click;

// 鉛筆/消しゴム
// 各色ブラシ/雑巾
// オブジェクト配置
//

void Game::preset()
{
	//Particle::set<Dust>(20);
	Draw::font = LoadFontDataToHandle("data/font/NotoSansJPLight.dft");
	for(int i = 0; i < 24; ++i)
	{
		map.grid.emplace_back(std::vector<Map::Grid>(32));
	}
}

Game::Message Game::update()
{
	if(Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}

	if(Mouse::wheel() != 0)
	{
		tool += Mouse::wheel();
		if(tool < 0)
			tool += 3;
		tool %= 3;
		toolmode = 0;
	}
	if(tool == 0)
	{
		if(Mouse::click(MOUSE_INPUT_1))
		{
			if(Mouse::y() > 0 && Mouse::y() < common::height && Mouse::x() > 0 && Mouse::x() < common::width)
			{
				Point<int> p = Mouse::pos();
				p.y %= 20;
				p.x %= 20;
				if(p.y < 4)
					click.y = Mouse::y() / 20;
				else if(p.y >= 16)
					click.y = Mouse::y() / 20 + 1;
				if(p.x < 4)
					click.x = Mouse::x() / 20;
				else if(p.x >= 16)
					click.x = Mouse::x() / 20 + 1;
			}
		}
		if(Mouse::button(MOUSE_INPUT_1) && Mouse::type())
		{
			if(Mouse::y() > 0 && Mouse::y() < common::height && Mouse::x() > 0 && Mouse::x() < common::width)
			{
				bool ac = true;
				Point<int> p = Mouse::pos();
				p.y %= 20;
				p.x %= 20;
				if(p.y < 4)
					p.y = Mouse::y() / 20;
				else if(p.y >= 16)
					p.y = Mouse::y() / 20 + 1;
				else
					ac = false;
				if(p.x < 4)
					p.x = Mouse::x() / 20;
				else if(p.x >= 16)
					p.x = Mouse::x() / 20 + 1;
				else
					ac = false;
				if(ac)
				{
					map.grid[p.y][p.x].paint = toolmode;
				}
			}
		}
	}
	else if(tool == 1)
	{
		if(Mouse::button(MOUSE_INPUT_1) && Mouse::type())
		{
			if(Mouse::y() > 0 && Mouse::y() < common::height && Mouse::x() > 0 && Mouse::x() < common::width)
			{
				map.grid[Mouse::y() / 20][Mouse::x() / 20].paint = toolmode;
			}
		}
		if(Mouse::click(MOUSE_INPUT_3))
		{
			toolmode ^= -1;
		}
	}

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	int x = 0, y = 0;
	for(const auto& i : map.grid)
	{
		for(const auto& j : i)
		{
			switch(j.paint)
			{
			case -1:
				display.box(x, y, 20, 20, 0xffe4e4c3, true);
				break;
			case 0:
				display.box(x, y, 20, 20, 0x65e37e, true);
				break;
			}
			if(j.line(0))
				display.box(x - 1, y - 1, 22, 2, 0x1e1e1e, true);
			if(j.line(1))
				display.box(x - 1, y - 1, 2, 22, 0x1e1e1e, true);
			display.blend(blendmode::alpha, 64);
			display.box(x, y, 20, 20, 0xa1b23f, false);
			display.blend();
			x += 20;
		}
		x = 0;
		y += 20;
	}

	//Particle::draw();
}

