#pragma once
#include <vector>

//床の構造体
struct Floor
{
	float x, y;//座標
	float width, height;//幅と高さ
};

// 床の初期化
void initFloors(Floor floors[],int& floorCount);

// 床の描画
void DrawFloors(Floor floors[], int& floorCount);