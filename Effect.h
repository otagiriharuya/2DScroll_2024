#pragma once

const int EffectNum = 100;
extern int img[10];//最大10コマ

struct Effect
{
	double x;
	double y;
	double animeNo = 0;//今のコマ
	int maxAnimeNo;//最大コマ数
	bool enable = false;//再生有効フラグ
};

extern Effect effect[EffectNum];//エフェクト用の変数

void initEffect();
void updateEffect();
void drawEffect();