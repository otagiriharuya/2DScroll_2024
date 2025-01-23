#include "DxLib.h"
#include "Effect.h"

Effect jump[EffectNum];//ジャンプ用の変数
int Jumpimg[5];//ジャンプ画像5コマ

void initEffect()
{
	//画像の読込
	LoadDivGraph("Jump.png", 5, 5, 1, 100, 100, Jumpimg);
}

void UpdateEffect()
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; i++)
	{
		if (jump[i].enable == true)
		{
			//アニメーションを進める
			jump[i].animeNo = jump[i].animeNo + 0.1;
			//６コマ目になったら終了
			if ((int)(jump[i].animeNo) > 5) {
				jump[i].enable = false;
			}
		}
	}
}

void DrawEffect()
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].enable == true)
		{
			int no = jump[i].animeNo;
			DrawGraph(jump[i].x, jump[i].y, Jumpimg[no], true);
		}
	}
}
