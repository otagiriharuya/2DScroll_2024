#pragma once
#include <vector>

//���̍\����
struct Floor
{
	float x, y;//���W
	float width, height;//���ƍ���
};

// ���̏�����
void initFloors(Floor floors[],int& floorCount);

// ���̕`��
void DrawFloors(Floor floors[], int& floorCount);