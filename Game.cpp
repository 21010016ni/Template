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

	// �������
	// �S�̎����̐ݒ�
	// �}�`�̐��i�}�`�����j
	// 
	// �}�`���Ƃ̐ݒ荀��
	//	�������[�h
	//	�J�n�t���[��
	// 
	// �~
	//	�p�̐�
	//	�h��Ԃ�
	// 
	// ���߂�o�^����
	// ����͂Ȃ񂩁A�����A���ڋt�|�[�����h�L�@�ŏ�������
	// ���u�L�@�͂Ȃ񂩂ˁA��ōl����
	// ���͕��@�́H
	// �L�[�{�[�h���́A�}�E�X���삪�ł���Ƃ���
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

