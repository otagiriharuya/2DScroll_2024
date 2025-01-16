#include "DxLib.h"
#include "Player.h"
#include "Action.h"

PlayerStatus player;//プレイヤーのステータス
void PlayerMove();//移動
void PlayerJump();//ジャンプ

//プレイヤー初期化
void initPlayer()
{
	player.Hp = 5;
	player.x = 40;
	player.y = 700;
	player.r = 35;
	player.vx = 2;
	player.vy = 5;
	player.isJump = false;
	player.JumpSu = 0;
	//player.img = 
}

//プレイヤー更新
void UpdatePlayer()
{
	PlayerMove();
	PlayerJump();
}

//移動
void PlayerMove()
{
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		player.x -= player.vx;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		player.x += player.vx;
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		player.y -= player.vy;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		player.y += player.vy;
	}
}

//ジャンプ
void PlayerJump()
{

}

//プレイヤー描画
void DrawPlayer()
{
	DrawCircle(player.x, player.y, player.r, GetColor(255, 255, 255), true);
}
