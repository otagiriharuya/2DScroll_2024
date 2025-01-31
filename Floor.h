#pragma once
#include "DxLib.h"

//床の構造体
struct Floor
{
    float x, y;//座標
    float width, height;//幅と高さ
    int img;//画像
};

#include "FloorManager.h"
void initFloors(FloorManager& floorManager);