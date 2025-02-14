#pragma once

//エフェクトの情報
struct Effect
{
	float x, y = 0;//座標
	float animeNo = 0;//現在のコマ数
	bool isUsed = false;//再生有効フラグ
};

const int JumpMaxNum = 5;
const int EffectNum = 100;

extern int Jumpimg[JumpMaxNum];//ジャンプ画像
extern Effect jump[EffectNum];//ジャンプ用変数

void InitEffect();//エフェクト初期化
void UpdateEffect(float deltaTime);//エフェクト更新
void DrawEffect();//エフェクト描画
void StartJumpEffect(float x, float y);//ジャンプエフェクト用関数