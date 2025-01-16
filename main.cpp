#include "DxLib.h"
#include "Player.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//ウィンドウモードで起動する
	SetGraphMode(1000, 800, 16);//画面のサイズとビット数変更

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	initPlayer();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		UpdatePlayer();
		DrawPlayer();
		ScreenFlip();//裏画面と表画面の入替
		ClearDrawScreen();//裏画面の描画を全て消去
	}
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return 0;// ソフトの終了 
}