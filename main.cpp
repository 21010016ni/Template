#include <DxLib.h>
#include "Config.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include "resource.h"

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

WNDPROC dxWndProc;
HWND hMainWnd;

LRESULT CALLBACK MyProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// 初期化
	LONGLONG count = 0;	// FPS調整用
	SetMainWindowText("Now Loading...");
	SetGraphMode(common::width, common::height, common::colorbit);
	// DxLib初期化ブロック
	//----------------------------------------------------------------<<
	ChangeWindowMode(TRUE);
	LoadMenuResource(IDR_MENU1);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	//---------------------------------------------------------------->>
	// 初期化
	if(DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	hMainWnd = GetMainWindowHandle();
	dxWndProc = (WNDPROC)GetWindowLong(hMainWnd, -4);
	SetWindowLong(hMainWnd, -4, (LONG)MyProc);
	// 初期化ブロック
	//----------------------------------------------------------------<<
	Game::preset();	

	//---------------------------------------------------------------->>
	// タイトル表示
	SetMainWindowText("");
	while(ProcessMessage() != -1)
	{
		count = GetNowHiPerformanceCount();
		// キーボード入力状況更新
		Keyboard::update();
		Mouse::update();
		// 処理ブロック
		//----------------------------------------------------------------<<
		if (Game::update() == Game::Message::quit)
			break;

		//---------------------------------------------------------------->>
		// 画面消去
		ClearDrawScreen();
		// 描画ブロック
		//----------------------------------------------------------------<<
		Game::draw();

		//---------------------------------------------------------------->>
		// 画面表示
		ScreenFlip();
		while(GetNowHiPerformanceCount() - count < 1000000 / common::fps);
	}
	// 終了処理
	SetMainWindowText("Process Quitting...");
	DxLib_End();
	return 0;
}

LRESULT MyProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case ID_END:
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, "テスト", "test", MB_OK);
		break;
	}
	return CallWindowProc(dxWndProc, hWnd, msg, wp, lp);
}

