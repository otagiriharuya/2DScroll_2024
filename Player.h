#pragma once
#include "Game.h"
#include "Floor.h"

//プレイヤーの構造体
extern struct  PlayerStatus
{
	float x, y;//座標
	float vx, vy;//移動量
	float Hp;//体力
	float r;//半径
	float jumpPower;//ジャンプ力
	int img;//画像
	int jumpCount;//ジャンプした回数
	int maxJumps;//最大ジャンプ数
	int staet;//現在の状態(0:地上1:1段ジャンプ中2:2段ジャンプ中3:落下中)
	bool isSpace;//スペースキーが押されたか
	Type type;
};

void initPlayer();//プレイヤー初期化
void UpdatePlayer(Floor floors[],int floorCount);//プレイヤー更新
void DrawPlayer();//プレイヤー描画
