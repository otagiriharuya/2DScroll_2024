#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include "Effect.h"
#include "Enemy.h"
#include "Camera.h"
#include "GameState.h"
#include <algorithm>
#include <math.h>

// 定数
const float Gravity = 7.0f;//重力
const float MAX_VY = 1000.0f; // 最大落下速度
const float MoveSpeed = 300.0f;//自機の移動スピード
const float JumpPower = -500.0f;//自機のジャンプ力
const int MaxJumps = 2;//最大ジャンプ数
const int WindowWidth = 2000;//ウィンドウの横最大数

PlayerStatus player;//プレイヤーインスタンス

//プレイヤー初期化関数
void InitPlayer()
{
	player.img = LoadGraph("Ghost.png", true);//画像
	player.x = 150;//x座標
	player.y = 600;//y座標
	player.vx = 0;//横移動量
	player.vy = 0;//縦移動量
	player.jumpPower = JumpPower;//ジャンプ力
	player.r = 25;//半径
	player.jumpCount = 0;//ジャンプした回数
	player.maxJumps = MaxJumps;//最大ジャンプ数
	player.isSpace = false;//Spaceキーを押したか
	player.isRight = true;//右を向いているか
	player.isAlive = true;//生きているか
	player.state = PlayerState::Ground;//現在の状態

	//体力画像読み込み
	player.hpFullImg = LoadGraph("Life1.0.png");//最大
	player.hpHalfImg = LoadGraph("Life0.5.png");//半分
	player.hpEmptyImg = LoadGraph("Life0.0.png");//空

	//体力関連初期化g
	player.maxHp = 5;//最大体力
	player.Hp = 5;//体力
	player.hitCoolDownTime = 1.0f;//クールダウンタイムを設定
	player.hitCoolDownTimer = 0.0f;//クールダウンタイマー
	player.hpX = 10;//体力表示X座標
	player.hpY = 10;//体力表示Y座標
	player.hpOffsetX = 40;//ハートの間隔
}

//プレイヤー更新関数
void UpdatePlayer(float deltaTime)
{
	PlayerMove();
	PlayerJump();
	PlayerGra();
	PlayerPosi(deltaTime);
	PlayerCollision(deltaTime);
	PlayerDeath();
}

//プレイヤー移動処理
void PlayerMove()
{
	float MS = MoveSpeed;
	//左シフトを押しているときダッシュ
	if (CheckHitKey(KEY_INPUT_LSHIFT))
		MS *= 2;
	//地面にいないときスピードリセット
	if (player.state != PlayerState::Ground)
		MS = MoveSpeed;

	//横移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		player.vx = -MS;
		player.isRight = false;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.vx = MS;
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

		//地面にいるかジャンプした回数が2回未満だったら
		if (player.state == PlayerState::Ground || player.jumpCount < player.maxJumps)
		{
			//ジャンプエフェクト
			StartJumpEffect(player.x - 50, player.y - 50);
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

//プレイヤー重力適用
void PlayerGra()
{
	//重力による落下
	player.vy += Gravity;
	//落下処理
	if (player.state != PlayerState::Ground && player.vy > 0)
		player.state = PlayerState::Falling;//落下中
}

//プレイヤー座標更新
void PlayerPosi(float deltaTime)
{
	//画面端処理
	if (player.x < player.r)
		player.x = player.r;
	if (player.x > WindowWidth - player.r)
		player.x = WindowWidth - player.r;
	//移動
	player.x += player.vx * deltaTime;
	if (player.vy >= MAX_VY)player.vy = MAX_VY;//最大落下速度を超える場合は制限
	player.y += player.vy * deltaTime;
}

//円と矩形の当たり判定
bool CheckCollision(float circleX, float circleY, float circleR,
	float rectX, float rectY, float rectWidth, float rectHeight)
{
	//円の中心と矩形の中心との距離を計算
	float distX = fabs(circleX - (rectX + rectWidth / 2));
	float distY = fabs(circleY - (rectY + rectHeight / 2));

	//円が矩形から離れている場合
	if (distX > (rectWidth / 2 + circleR))
		return false;//衝突していない
	if (distY > (rectHeight / 2 + circleR))
		return false;//衝突していない

	//円の中心が矩形の内側にある場合
	if (distX <= (rectWidth / 2))
		return true;//衝突している
	if (distY <= (rectHeight / 2))
		return true;//衝突している

	//角の衝突判定
	float dx = distX - rectWidth / 2;
	float dy = distY - rectHeight / 2;
	//内側にめり込んでいるか判定
	return (dx * dx + dy * dy <= (circleR * circleR));
}

//円同士の当たり判定
bool CheckCollisionCircles(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));//距離
	return distance < r1 + r2;//当たっているか
}

//プレイヤー当たり判定
void PlayerCollision(float deltaTime)
{
	//床との当たり判定
	bool isCollision = false;
	//床の数分回す
	for (int i = 0; i < MaxFloors; ++i)
	{
		if (CheckCollision(player.x, player.y, player.r,
			floors[i].x, floors[i].y, floors[i].width, floors[i].height))
		{
			isCollision = true;
			//当たり判定時の処理（例：落下を止める）
			if (player.vy > 0) {
				float penetration = (player.y + player.r) - floors[i].y; // めり込み量を計算
				player.y -= penetration; // めり込み量だけ戻す
				player.vy = 0;
				player.state = PlayerState::Ground;
				player.jumpCount = 0;
			}
		}
	}

	//地面にいない場合
	if (!isCollision)
		player.state = PlayerState::Falling;

	//当たり判定クールダウンタイマーを更新
	if (player.hitCoolDownTimer > 0.0f)
	{
		player.hitCoolDownTimer -= deltaTime;
	}

	float damage = 0.5f; //一度に減らす体力

	//敵との当たり判定
    float enemyRadius = enemy.width / 2.0f;
	//
	if (enemy.isAlive && player.hitCoolDownTimer <= 0.0f && CheckCollisionCircles(player.x, player.y, player.r, enemy.x, enemy.y, enemyRadius))
	{
		//減らす体力が現在のHPを超えないようにする
		if (damage > player.Hp)
		{
			damage = player.Hp;
		}
		player.Hp -= damage;//体力を減らす

		if (player.Hp < 0.0f)
			player.Hp = 0.0f;//体力が0未満にならないようにする
		player.hitCoolDownTimer = player.hitCoolDownTime;//クールダウンタイマーをリセット
	}
}

//プレイヤー死亡判定
void PlayerDeath()
{	//体力が0以下になったら
	if (player.Hp <= 0)
	{
		player.Hp = 0;
		player.isAlive = false;
		//ゲームオーバー状態にする
		gameState = GameState::GameOver;//ゲームオーバー状態にする
	}
	//落下して体力が残っていたら
	if (player.y >= 800 && player.Hp > 0)
	{
		player.Hp--;
		player.isRight = true;
		player.x = 150;//x座標
		player.y = 600;//y座標
	}
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", player.Hp);
}


//プレイヤー描画関数
void DrawPlayer()
{
	//描画先のX座標,描画先のY座標,画像,透過するか,反転させるか
	DrawReverseGraph(WorldToScreenX(camera, player.x - 25), WorldToScreenY(camera, player.y - 25),
		player.img, true, !player.isRight);

	DrawHp();
}

//体力描画関数
void DrawHp()
{
    for (int i = 0; i < player.maxHp; ++i)
    {
        int imgHandle = player.hpEmptyImg;//最初は空のハート

        if (player.Hp >= i + 1)
        {
            imgHandle = player.hpFullImg;//満タンのハート
        }
        else if (player.Hp > i && player.Hp < i + 1)//半分表示
        {
            imgHandle = player.hpHalfImg;//半分のハート
        }

        DrawGraph(player.hpX + i * player.hpOffsetX, player.hpY, imgHandle, TRUE);
    }
}