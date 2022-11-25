#include "Game.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "Effect.hpp"
#include "ParticleDust.hpp"

void Game::preset()
{
	Particle::set<Dust>(20);
}

Draw Game::main(common::width / 2, common::height / 2, 0);
Draw Game::ui(0, 0, 1);

Game::Message Game::update()
{
	static int effect = -1;
	if (Mouse::click(MOUSE_INPUT_1))
	{
		if(effect == -1)
		{
			//Effect::TestWrite();
			effect = Effect::load("data.bin");
		}
		Effect::emit(Mouse::x(), Mouse::y(), effect);
	}

	// つくるやつやる
	// 全体寿命の設定
	// 図形の数（図形を作る）
	// 
	// 図形ごとの設定項目
	//	合成モード
	//	開始フレーム
	// 
	// 円
	//	角の数
	//	塗りつぶし
	// 
	// 命令を登録する
	// これはなんか、もう、直接逆ポーランド記法で書かせる
	// 中置記法はなんかね、後で考える
	// 入力方法は？
	// キーボード入力、マウス操作ができるといい
	//

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

