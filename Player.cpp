#include "DxLib.h"
#include "Player.h"
#include "Action.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

PlayerStatus player;//プレイヤーのステータス
std::vector<Floor> floors;

//プレイヤー初期化
void initPlayer()
{
	//player.img = LoadGraph("");
	player.Hp = 5;
	player.x = 100;
	player.y = 300;
	player.vx = 0;
	player.vy = 0;
	player.jumpPower = -11.0f;//ジャンプ力
	player.r = 50;
	player.jumpCount = 0;
	player.maxJumps = 2;
	player.isSpace = false;
	player.staet = 0;
	
}

//プレイヤー更新
void UpdatePlayer(Floor floors[], int floorCount)
{
	PlayerMove();//移動
	PlayerJump();//ジャンプ
	PlayerGra();//重力
	PlayerCollision(floors, floorCount);//当たり判定
	PlayerPosi();//座標
}

//プレイヤー移動処理
void PlayerMove()
{
	const float Move_Speed = 5;//横移動量
	//横移動
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		player.vx = -Move_Speed;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		player.vx = Move_Speed;
	}
	else
	{
		player.vx = 0;
	}
}

//プレイヤージャンプ処理
void PlayerJump()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && !player.isSpace)
	{
		player.isSpace = true;
		//ジャンプエフェクト
		for (int i = 0; i < EffectNum; ++i)
		{
			if (jump[i].enable == false)
			{
				jump[i].enable = true;
				jump[i].x = player.x - 50;
				jump[i].y = player.y - 50;
				jump[i].animeNo = 0;
				break;
			}
		}
		//地面にいるかジャンプした回数が2回未満だったら
		if (player.staet == 0 || player.jumpCount < player.maxJumps)
		{
			player.vy = player.jumpPower;//y方向の移動量をジャンプ力にする
			++player.jumpCount;//ジャンプ回数を増やす
			if (player.staet == 0)
				player.staet = 1;//1回目のジャンプ
			else if (player.staet == 1)
				player.staet = 2;//2回目のジャンプ
		}
	}
	if (!CheckHitKey(KEY_INPUT_SPACE))
		player.isSpace = false;
}

//プレイヤー重力処理
void PlayerGra()
{
	//重力による落下
	player.vy += Gravity;
	//落下処理
	if (player.staet != 0 && player.vy > 0)
		player.staet = 3;//落下中
}

//プレイヤーの床との衝突判定
void PlayerCollision(Floor floors[], int floorCount)
{
	//床との当たり判定
	player.staet = 3;//いったん地面についていない状態にする
	for (int i = 0; i < floorCount; ++i)
	{
		Floor& floor = floors[i];//床情報代入
		bool isColliding = CheckCollision(player.x, player.y, player.r
			, floor.x, floor.y, floor.width, floor.height);
		//当たり判定があったときの処理
		if (isColliding)
		{
			if (player.vy >= 0 && player.y - player.r < floor.y)
			{
				// 床の上からの衝突
				player.y = floor.y - player.r;
				player.vy = 0;
				player.staet = 0;
				player.jumpCount = 0;
			}
			else if (player.vy <= 0 && player.y + player.r > floor.y + floor.height)
			{
				// 床の下からの衝突
				player.y = floor.y + floor.height + player.r;
				player.vy = 0;
			}
		}
	}
}

//プレイヤー座標更新
void PlayerPosi()
{
	// 画面端処理
		if (player.x < player.r) player.x = player.r;
	if (player.x > 1000 - player.r) player.x = 1000 - player.r;
	// 移動
	player.x += player.vx;
	player.y += player.vy;
}

//プレイヤー描画
void DrawPlayer()
{
	DrawCircle(player.x,player.y,player.r, GetColor(255, 255, 255), true);
	//DrawGraph(Cha_Player.x, Cha_Player.y, Cha_Player.img, true);

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ｘ：%f,ｙ：%f\n%d",Obj_Player.x,Obj_Player.y,player.jumpCount);
}
