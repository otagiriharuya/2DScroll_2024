#pragma once

//���̏��
struct Floor
{
	float x, y;//���W
	float width, height;//�����ƕ�
};
static const int MaxFloors = 6;
extern Floor floors[MaxFloors];

void InitMap();//�}�b�v������
void UpdateMap();//�}�b�v�X�V
void DrawMap();//�}�b�v�`��