#pragma once

const int EffectNum = 100;
extern int Jumpimg[5];//ジャンプ画像5コマ

struct Effect
{
	float x;
	float y;
	float animeNo = 0;//今のコマ
	int maxAnimeNo;//最大コマ数
	bool enable = false;//再生有効フラグ
};

extern Effect jump[EffectNum];//ジャンプ用の変数

void initEffect();
void UpdateEffect();
void DrawEffect();