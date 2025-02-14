#pragma once

//床の情報
struct Floor
{
	float x, y;//座標
	float width, height;//高さと幅
};
static const int MaxFloors = 6;
extern Floor floors[MaxFloors];

void InitMap();//マップ初期化
void UpdateMap();//マップ更新
void DrawMap();//マップ描画