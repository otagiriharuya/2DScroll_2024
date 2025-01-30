#include "DxLib.h"
#include <vector>
#include <algorithm>
#include <cmath>//std::powを使用するため
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

//定数
const float PlayerMoveSpeed = 3.0f;//自機の移動スピード
const float PlayerJumpPower = -11.0f;//自機のジャンプ力
const int PlayerMaxJumps = 2;//最大ジャンプ数
const int WindowWidth = 1000;//ウィンドウの横最大数

PlayerStatus player;

//プレイヤー初期化
void initPlayer()
{
	player.img = LoadGraph("Ghost.png",true);//画像
	player.Hp = 5;//体力
	player.x = 500;//x座標
	player.y = 300;//y座標
	player.vx = 0;//横移動量
	player.vy = 0;//縦移動量
	player.jumpPower = PlayerJumpPower;//ジャンプ力
	player.r = 25;//半径
	player.jumpCount = 0;//ジャンプした回数
	player.maxJumps = PlayerMaxJumps;//最大ジャンプ数
	player.isSpace = false;//Spaceキーを押したか
	player.isRight = true;//右を向いているか
	player.state = PlayerState::Ground;//現在の状態
}

//重力加速度敵用
void PlayerGra()
{
	//重力による落下
	player.vy += Gravity;
	//落下処理
	if (player.state != PlayerState::Ground && player.vy > 0)
		player.state = PlayerState::Falling;//落下中
}

//プレイヤー移動処理
void PlayerMove()
{
	float MoveSpeed = PlayerMoveSpeed;//横移動量

	//左シフトを押しているときダッシュ
	if (CheckHitKey(KEY_INPUT_LSHIFT))
		MoveSpeed *= 2;
	//地面にいるとき
	if (player.state != PlayerState::Ground)
		MoveSpeed = PlayerMoveSpeed;

	//横移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		player.vx = -MoveSpeed;
		player.isRight = false;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.vx = MoveSpeed;
		player.isRight = true;
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
		StartJumpEffect(player.x - 50, player.y - 50);

		//地面にいるかジャンプした回数が2回未満だったら
		if (player.state == PlayerState::Ground || player.jumpCount < player.maxJumps)
		{
			player.vy = player.jumpPower;//y方向の移動量をジャンプ力にする
			++player.jumpCount;//ジャンプ回数を増やす
			if (player.state == PlayerState::Ground)
				player.state = PlayerState::Jump1;//状態をジャンプ1回目に
			else if (player.state == PlayerState::Jump1)
				player.state = PlayerState::Jump2;//状態をジャンプ2回目に
		}
	}
	if (!CheckHitKey(KEY_INPUT_SPACE))
		player.isSpace = false;
}

//床との衝突判定
bool CheckCollision(float playerX, float playerY, float playerR,const Floor& floor)
{
	//円と矩形の当たり判定
	float circleDistanceX = std::abs(playerX - floor.x - floor.width / 2);
	float circleDistanceY = std::abs(playerY - floor.y - floor.height / 2);

	if (circleDistanceX > (floor.width / 2 + playerR)) { return false; }
	if (circleDistanceY > (floor.height / 2 + playerR)) { return false; }

	if (circleDistanceX <= (floor.width / 2)) { return true; }
	if (circleDistanceY <= (floor.height / 2)) { return true; }

	float cornerDistanceSq = (circleDistanceX - floor.width / 2) * (circleDistanceX - floor.width / 2) +
		(circleDistanceY - floor.height / 2) * (circleDistanceY - floor.height / 2);

	return (cornerDistanceSq <= (playerR * playerR));
}

//プレイヤーの床との衝突判定
void PlayerCollision(const std::vector<Floor>& floors)
{
	player.state = PlayerState::Falling;
	for (const auto& floor : floors)
	{
		bool isColliding = CheckCollision(player.x, player.y, player.r, floor);
		if (isColliding)
		{
			if (player.vy >= 0 && player.y - player.r < floor.y)
			{
				player.y = floor.y - player.r;
				player.vy = 0;
				player.state = PlayerState::Ground;
				player.jumpCount = 0;
			}
			else if (player.vy <= 0 && player.y + player.r > floor.y + floor.height)
			{
				player.y = floor.y + floor.height + player.r;
				player.vy = 0;
			}
		}
	}
}

//プレイヤー座標更新
void PlayerPosi()
{
	//画面端処理
	if (player.x < player.r) 
		player.x = player.r;
	if (player.x > 1000 - player.r) 
		player.x = 1000 - player.r;
	//移動
	player.x += player.vx;
	player.y += player.vy;
}

//プレイヤー更新
void UpdatePlayer(const std::vector<Floor>& floors, float deltaTime)
{
	PlayerMove();//移動
	PlayerJump();//ジャンプ
	PlayerGra();//重力
	PlayerCollision(floors);//当たり判定
	PlayerPosi();//座標

}

//プレイヤー描画
void DrawPlayer()
{
	//DrawCircle(player.x,player.y,player.r, GetColor(255, 255, 255), false);
	DrawReverseGraph(player.x-player.r, player.y-player.r, player.img, true,!player.isRight);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ｘ：%f,ｙ：%f\n%d",Obj_Player.x,Obj_Player.y,player.jumpCount);
}
