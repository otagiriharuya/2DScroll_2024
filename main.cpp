#include "DxLib.h"
#include <chrono>
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "FloorManager.h"
#include "Floor.h"

//グローバルインスタンス
FloorManager floorManager;

//プロトタイプ宣言
void GameInitResources();//ゲームリソースの初期化
void GameInitObj();//ゲームオブジェの初期化
void GameUpdate(float deltaTime);//ゲームの更新
void GameDraw();//ゲームの描画
std::chrono::system_clock::time_point prevTime;//時間計測用

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

	GameInitResources();//ゲームリソースの初期化
	GameInitObj();//ゲームオブジェの初期化

	prevTime = std::chrono::system_clock::now();//前回時間を取得

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//裏画面の描画を全て消去
		//時間計測
		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();//現在時間取得
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - prevTime).count() / 1000000.0f;
		prevTime = currentTime;

		GameUpdate(deltaTime);//更新
		GameDraw();//描画

		ScreenFlip();//裏画面と表画面の入替
	}
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return 0;// ソフトの終了 
}

//ゲームリソース初期化
void GameInitResources()
{
	initEffect();
}

//ゲームオブジェ初期化
void GameInitObj()
{
	initPlayer();
	initFloors(floorManager);
}

//ゲーム更新
void GameUpdate(float deltaTime)
{
	UpdateEffect(deltaTime);
	UpdatePlayer(floorManager.GetFloors(), deltaTime);

	// 例：スペースキーを押したら新しい床を追加
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		Floor newFloor = { 100, 100, 50, 50 };
		newFloor.img = LoadGraph("Bloc01.jpg", true);
		floorManager.AddFloor(newFloor);
	}

	if (CheckHitKey(KEY_INPUT_1) == 1) {
		// 例：x座標が500以上の床を削除
		floorManager.RemoveFloorIf([](const Floor& floor) { return floor.x > 500; });
	}
}

//ゲーム描画
void GameDraw()
{
	DrawEffect();
	DrawPlayer();
	floorManager.DrawFloors();
}