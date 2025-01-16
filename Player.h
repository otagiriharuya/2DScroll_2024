#pragma once

void initPlayer();//プレイヤー初期化
void UpdatePlayer();//プレイヤー更新
void DrawPlayer();//プレイヤー描画

//プレイヤーのステータス
extern struct  PlayerStatus
{
	double Hp;//体力
	double x;//x座標
	double y;//y座標
	double r;//半径
	double vx;//xの移動量
	double vy;//yの移動量
	int img;//画像
	int JumpSu;//ジャンプした回数
	bool isJump;//ジャンプしたか
};
