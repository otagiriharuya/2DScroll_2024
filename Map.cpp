#include "DxLib.h"
#include "Map.h"
#include "Camera.h"

Floor floors[MaxFloors];

//マップ初期化
void InitMap()
{
	//床初期化
	floors[0] = { 100,600,200,50 };
	floors[1] = { 400,400,150,50 };
	floors[2] = { 600,500,250,50 };
	floors[3] = { 1100,600,200,50 };
	floors[4] = { 1400,400,150,50 };
	floors[5] = { 1600,500,250,50 };
}

//マップ更新
void UpdateMap()
{

}

//マップ描画
void DrawMap()
{
	for (int i = 0; i < MaxFloors; ++i)
	{
		DrawBox(WorldToScreenX(camera, floors[i].x), WorldToScreenY(camera, floors[i].y),
			WorldToScreenX(camera, floors[i].x + floors[i].width), WorldToScreenY(camera, floors[i].y + floors[i].height),
			GetColor(255, 255, 255), true);
	}
}