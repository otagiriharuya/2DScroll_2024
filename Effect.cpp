#include "DxLib.h"
#include "Effect.h"
#include "Camera.h"

Effect jump[EffectNum];//ジャンプ用変数
int Jumpimg[JumpMaxNum];//ジャンプ画像
const float AnimationSpeed = 10.0f;//アニメーション速度

//エフェクト初期化
void InitEffect()
{
	//画像の読込
	LoadDivGraph("Jump.png", 5, 5, 1, 100, 100, Jumpimg);
	//ジャンプエフェクトの初期化
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].isUsed = false;
		jump[i].animeNo = 0;
		jump[i].x = 0;
		jump[i].y = 0;
	}
}

//エフェクトの更新
void UpdateEffect(float deltaTime)
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].animeNo += AnimationSpeed * deltaTime;//アニメーションを進める
		//コマ数を超えたらエフェクトを終了させる
		if (jump[i].animeNo >= JumpMaxNum)
		{
			jump[i].isUsed = false;
			jump[i].animeNo = 0;
		}
	}
}

//エフェクト描画
void DrawEffect()
{
	//ジャンプ用
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].isUsed)
		{
			int no = jump[i].animeNo;
			DrawGraph(WorldToScreenX(camera, jump[i].x), WorldToScreenY(camera, jump[i].y), Jumpimg[no], true);
		}
	}
}

//ジャンプエフェクト用関数
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