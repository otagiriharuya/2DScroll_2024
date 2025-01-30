#pragma once
#include <vector>
#include <cstdint>//int32_tを使用するため

//床の構造体
struct Floor
{
	float x, y;//座標
	float width, height;//幅と高さ
	int img;//画像
};

extern std::vector<Floor> floors;

//床の初期化
void initFloors();

//床の描画
void DrawFloors();