#pragma once
#include <vector>

const int JumpMaxNum = 5;//ジャンプエフェクトの最大コマ数
const int EffectNum = 100;//エフェクト最大数

struct Effect
{
	float x,y =0;//座標
	int animeNo = 0;//現在のコマ数
	bool isUsed = false;//再生有効フラグ
};

//ジャンプエフェクトの配列
extern std::vector<int> Jumpimg;//ジャンプ画像
extern std::vector<Effect> jump;//ジャンプ用の変数

void initEffect();
void UpdateEffect(float deltaTime);
void DrawEffect();
void StartJumpEffect(float x, float y);