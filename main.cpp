#include <DxLib.h>
#include "Config.hpp"
#include "Input.hpp"
#include "Game.hpp"

//#define USE_CONSOLE

int common::width = 640;
int common::height = 480;
int common::colorbit = 32;
int common::fps = 60;

std::mt19937 common::engine(std::random_device{}());

#ifdef USE_CONSOLE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
int main() { return WinMain(GetModuleHandle(0), NULL, NULL, _Notnull_ SW_SHOWDEFAULT); }
#endif // USE_CONSOLE

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// ������
	LONGLONG count = 0;	// FPS�����p
	SetMainWindowText("Now Loading...");
	SetGraphMode(common::width, common::height, common::colorbit);
	// DxLib�������u���b�N
	//----------------------------------------------------------------<<
	ChangeWindowMode(TRUE);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	//---------------------------------------------------------------->>
	// ������
	if(DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	// �������u���b�N
	//----------------------------------------------------------------<<
	Game::preset();	

	//---------------------------------------------------------------->>
	// �^�C�g���\��
	SetMainWindowText("");
	while(ProcessMessage() != -1)
	{
		count = GetNowHiPerformanceCount();
		// �L�[�{�[�h���͏󋵍X�V
		Keyboard::update();
		Mouse::update();
		// �����u���b�N
		//----------------------------------------------------------------<<
		if (Game::update() == Game::Message::quit)
			break;

		//---------------------------------------------------------------->>
		// ��ʏ���
		ClearDrawScreen();
		// �`��u���b�N
		//----------------------------------------------------------------<<
		Game::draw();

		//---------------------------------------------------------------->>
		// ��ʕ\��
		ScreenFlip();
		while(GetNowHiPerformanceCount() - count < 1000000 / common::fps);
	}
	// �I������
	SetMainWindowText("Process Quitting...");
	DxLib_End();
	return 0;
}

