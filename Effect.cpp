#include "DxLib.h"
#include "Effect.h"

std::vector<Effect> jump(EffectNum);//ジャンプ用変数
std::vector<int> Jumpimg(5);//ジャンプ画像

void initEffect()
{
	//画像の読込
	int result01 = LoadDivGraph("Jump.png", 5, 5, 1, 100, 100,Jumpimg.data());
	//エラー処理
	if(result01 == -1)
		MessageBox(nullptr, "画像の読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);

	//ジャンプエフェクトの初期化
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].isUsed = false;
		jump[i].animeNo = 0;
		jump[i].x = 0;
		jump[i].y = 0;
	}
}

void UpdateEffect(float deltaTime)
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].animeNo++;//アニメーションを進める
		//コマ数を超えたらエフェクトを終了させる
		if (jump[i].animeNo >= JumpMaxNum)
		{
			jump[i].isUsed = false;
			jump[i].animeNo = 0;
		}
	}
}

void DrawEffect()
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].isUsed == true)
		{
			int no = jump[i].animeNo;
			DrawGraph(jump[i].x, jump[i].y, Jumpimg[no % JumpMaxNum], true);
		}
	}
}

//ジャンプエフェクトを開始する関数
void StartJumpEffect(float x, float y)
{
	for (int i = 0; i < EffectNum; ++i)
	{
		if (!jump[i].isUsed)
		{
			jump[i].isUsed = true;
			jump[i].x = x;
			jump[i].y = y;
			jump[i].animeNo = 0;
			break;
		}
	}
}