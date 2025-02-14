#pragma once

//ゲームの状態
enum class GameState
{
	Title,//タイトル画面
	Game,//ゲーム画面
	Pause,//ポーズ画面
	GameOver//ゲームオーバー画面
};

extern GameState gameState;