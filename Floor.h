#pragma once
#include "DxLib.h"

//°‚Ì\‘¢‘Ì
struct Floor
{
    float x, y;//À•W
    float width, height;//•‚Æ‚‚³
    int img;//‰æ‘œ
};

#include "FloorManager.h"
void initFloors(FloorManager& floorManager);