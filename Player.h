#pragma once
#include <vector>
#include "Game.h"
#include "Floor.h"

enum class PlayerState
{
	Ground,//地面にいる
	Jump1,//ジャンプ1回目
	Jump2,//ジャンプ2回目
	Falling,//落下中
};

//プレイヤーの構造体
struct  PlayerStatus
{
	float x, y;//座標
	float vx, vy;//移動量
	float Hp;//体力
	float r;//半径
	float jumpPower;//ジャンプ力
	int img;//画像
	int jumpCount;//ジャンプした回数
	int maxJumps;//最大ジャンプ数
	bool isSpace;//スペースキーが押されたか
	bool isRight;//右を向いているか
	PlayerState state;//現在の状態
	Type type;
};

extern PlayerStatus player;

void initPlayer();//プレイヤー初期化
void UpdatePlayer(const std::vector<Floor>& floors,float deltaTime);//プレイヤー更新
void PlayerMove();//プレイヤー移動処理
void PlayerJump();//プレイヤージャンプ処理
void PlayerGra();//プレイヤー重力処理
void PlayerCollision(const std::vector<Floor>& floors);//プレイヤーの床との衝突判定と処理
void PlayerPosi();//プレイヤー座標更新
void DrawPlayer();//プレイヤー描画
