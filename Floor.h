#pragma once
#include "DxLib.h"

//���̍\����
struct Floor
{
    float x, y;//���W
    float width, height;//���ƍ���
    int img;//�摜
};

#include "FloorManager.h"
void initFloors(FloorManager& floorManager);